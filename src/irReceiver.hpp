#ifndef IRRECEIVER_HPP
#define IRRECEIVER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

namespace target = hwlib::target;

class IrReceiver : public rtos::task<>
{
private:
    uint16_t signal = 0;
    uint8_t player  = 0;
    uint8_t data    = 0;
    uint8_t control = 0;
    
    rtos::clock ten_us_clock;
    
public:
    IrReceiver(uint8_t player, uint8_t data):
	    task( "Ir Receiver" ),
        player(player),
        data(data),
		ten_us_clock( this, 10, "Ten us clock" )
    {}

    void main() override {
        auto receiverData = target::pin_in( target::pins::d8 );
        auto receiverGround    = target::pin_out( target::pins::d9 );
        auto receiverVcc    = target::pin_out( target::pins::d10 );
        receiverGround.set( 0 );
        receiverVcc.set( 1 );

        auto startReceiving = hwlib::now_us();
        bool receivingIr = false;
        int delay = 0;
        int count = 15;
        uint16_t signal = 0;
        for(;;){
            
            if( receiverData.get() == 0 && receivingIr == false ){
                receivingIr = true;
                startReceiving = hwlib::now_us();
            }
            if( receiverData.get() == 1 && receivingIr == true ){
                receivingIr = false;
                delay = ( hwlib::now_us() - startReceiving );
                if( delay > 600 && delay < 1000 ){
                    signal |= 0x00 << count;
                    count--;
                }
                else if( delay > 1400 && delay < 1800 ){
                    signal |= 0x01 << count;
                    count--;
                }
				else if( delay > 4000 ){
					count = 15;
				}
                if (count < 0) {
					for( int i = 15; i >= 0; --i) {
						hwlib::cout << ((signal >> i) & 1);
					}
					player = signal >> 10;
					player &= 0x1F;
					data = signal >> 5;
					data &= 0x1F;
					control = signal & 0x1F;
                    hwlib::cout << " Player: " << (int)player << " Data: " << (int)data << " Control: " << (( control == (player ^ data) ) ? "Yes" : "No" ) << hwlib::endl;
                    count = 15;
					signal = 0;
                }
            }
			
        }
    }
};


#endif // IRRECEIVER_HPP