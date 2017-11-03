#pragma once

#include "hwlib.hpp"

//#define TWI_SPEED = (100000)
//#define MCK_SPEED = (84000000)

#define TWI_CWGR_FREQ_RATIO(busclk, mck)	(((mck) >> 1) / (busclk))
#define TWI_CWGR_MIN_FREQ_RATIO				(4)
#define TWI_CWGR_CLDIV_MAX_VALUE			(0xFFu)
#define TWI_CWGR_CLDIV1(value)				((value) & TWI_CWGR_CLDIV_MAX_VALUE)
#define TWI_CWGR_CHDIV1(value) 				(TWI_CWGR_CLDIV(value) << 8)
#define TWI_CWGR_CKDIV_MAX_VALUE			(7u)
#define TWI_CWGR_CKDIV1(value) 				(((value) & TWI_CWGR_CKDIV_MAX_VALUE) << 16)
#define TWI_STANDARD_MODE_SPEED 100000U
#define TWI_FAST_MODE_SPEED 400000U

namespace due
{

	class twi_bus_due : public hwlib::i2c_bus{
	private:
		void write_byte(uint8_t byte) {
			TWI0->TWI_THR = byte;
			//hwlib::cout << "private write_byte fired" << hwlib::endl;
			//while((TWI0->TWI_SR & TWI_SR_TXCOMP) != TWI_SR_TXCOMP);
		}
		
	public:
		void write(uint_fast8_t a, const uint8_t data[], size_t n ) override {
			TWI0->TWI_MMR = 0;
			TWI0->TWI_MMR = 0 << 12 | a << 16;
			//TWI0->TWI_MMR |= TWI_MMR_MASTER_WRITE;
	
			TWI0->TWI_IADR = 0;
			
			uint32_t status = 0;

			for(size_t i = 0; i < n; ++i) {
				status = TWI0->TWI_SR;
				if (status & TWI_SR_NACK)
					hwlib::cout << "status & NACK" << hwlib::endl;
					//return 1;
				
				if (status & TWI_SR_TXRDY) {
					TWI0->TWI_THR = *(data + i);
					//hwlib::cout << *(data + i) << hwlib::endl;
					hwlib::wait_ns(28000);
				}
					//write_byte(data[i]);
			}
			
			while(1) {
				status = TWI0->TWI_SR;
				if (status & TWI_SR_NACK)
					hwlib::cout << "status & NACK" << hwlib::endl;
					//return 1;
				if (status & TWI_SR_TXRDY) {
					//hwlib::cout << "status & TXRDY" << hwlib::endl;
					break;
				}
			}
			
			TWI0->TWI_CR = TWI_CR_STOP;
			while (!(TWI0->TWI_SR & TWI_SR_TXCOMP));

			//while((TWI0->TWI_SR & TWI_SR_TXRDY) != TWI_SR_TXRDY);
		}

		void read(uint_fast8_t a, 
					uint8_t data[], 
					size_t n ) override {
						
		}

		twi_bus_due() {
			auto config_pin = [](uint32_t pin) {
				PIOA->PIO_ABSR &= (~pin & PIOA->PIO_ABSR);
				PIOA->PIO_PDR = pin;
				PIOA->PIO_IDR = pin;
				PIOA->PIO_PUER = pin;
			};
	
			config_pin(PIO_PA18A_TWCK0);
			config_pin(PIO_PA17A_TWD0);
		
			if ((PMC->PMC_PCSR0 & (1 << ID_TWI0)) != (1 << ID_TWI0))
				PMC->PMC_PCER0 = 1 << ID_TWI0;

			TWI0->TWI_CR = TWI_CR_SVEN;
			TWI0->TWI_CR = TWI_CR_SWRST;
			
			TWI0->TWI_CR = TWI_CR_SVDIS;
			TWI0->TWI_CR = TWI_CR_MSDIS;
			
			TWI0->TWI_CR = TWI_CR_MSEN;

			uint32_t dwCkDiv = 0;
			uint32_t dwClDiv = 0;
			uint32_t dwOk = 0;
			//uint32_t freq_ratio = (((48000000) >> 1) / (400000));
			//uint32_t freq_ratio = 5;
			
			/*if ((100000 > TWI_FAST_MODE_SPEED) || (freq_ratio < TWI_CWGR_MIN_FREQ_RATIO)) {
				hwlib::cout << "100000 > TWI_FAST_MODE or freq_ratio < MIN_FREG_RATIO" << hwlib::endl;
			}*/

			while(!dwOk) {
				dwClDiv = ((84000000 / (2 * 400000)) - 4) / (1<<dwCkDiv);

				if(dwClDiv <= 255)
					dwOk = 1;
				else
					dwCkDiv++;
			};

			/*while (1) {
				// Minimum freg = 4
				dwClDiv = (freq_ratio - TWI_CWGR_MIN_FREQ_RATIO) >> dwCkDiv;
				// does Clock Low Divider fit within 8 bits?
				if (dwClDiv <= TWI_CWGR_CLDIV_MAX_VALUE) {
					dwClDiv = TWI_CWGR_CLDIV_MAX_VALUE;
					//dwClDiv = 254;
					hwlib::cout << "dwClDiv <= MAX_VALUE" << hwlib::endl;
					break;		// cancel further calculation!
				}
		
				dwCkDiv++;
				// Clock Divider to large? (invalid parameters)
				if (dwCkDiv > TWI_CWGR_CKDIV_MAX_VALUE) {
					//dwCkDiv = TWI_CWGR_CKDIV_MAX_VALUE;
					hwlib::cout << "dwCkDiv > MAX_VALUE" << hwlib::endl;
					break;	// indicate "failure" !
				}
			}*/
			TWI0->TWI_CWGR = 0;
			// Set clock waveform generator register 
			TWI0->TWI_CWGR = TWI_CWGR_CLDIV1(dwClDiv) | TWI_CWGR_CHDIV1(dwClDiv) | TWI_CWGR_CKDIV1(dwCkDiv);
		
			//hwlib::cout << dwClDiv << "\n" << hwlib::endl;

			//TWI0->TWI_CWGR = 0;
			//TWI0->TWI_CWGR = (dwCkDiv << 16) | (dwClDiv << 8) | dwClDiv;
		}

	};

}
