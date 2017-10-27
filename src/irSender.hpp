#ifndef IRSENDER_HPP
#define IRSENDER_HPP

#include "hwlib.hpp"
namespace target = hwlib::target;

class IrSender
{
private:
    uint16_t signal = 0; //0: Startbit(1), 1-5: Speler(1-31), 6-10: Data(0-31), 11-15: Controlebits(11 XOR van 1 & 6, 12 XOR van 2 & 7 etc.)
    uint8_t player  = 0;
    uint8_t data    = 0;
    uint8_t control = 0;
    
    target::d2_36kHz irLed = target::d2_36kHz();
	
	void send_signal(){
		for( int i = 15; i >= 0; --i) {
			//hwlib::cout << ((signal >> i) & 1);
            if ((signal >> i) & 1) {
                sendOne();
            } else {
                sendZero();
            }
        }
		//hwlib::cout << hwlib::endl;
	}
public:
    IrSender(uint8_t player, uint8_t data):
    player(player),
    data(data)
    {}
    
    void sendOne() {
        irLed.set(1);
        hwlib::wait_us(1600);//Vervang met rtos!
        irLed.set(0);
        hwlib::wait_us(800);
    }
    
    void sendZero() {
        irLed.set(1);
        hwlib::wait_us(800);//Vervang met rtos!
        irLed.set(0);
        hwlib::wait_us(1600);
    }
    
    uint16_t generateSignal(uint8_t player, uint8_t data) {
        uint16_t signal = 0;
        signal |= 1 << 15;
        signal |= player << 10;
        signal |= data << 5;
        signal |= player ^ data; // Control XOR
        
        return signal;
    }
    
    void send() {
        signal = generateSignal(player, data);
        send_signal();
		hwlib::wait_ms(3); //Vervang met rtos!
		send_signal();
		hwlib::wait_ms(4);
    }
};

#endif // IRSENDER_HPP