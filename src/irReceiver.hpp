#ifndef IRRECEIVER_HPP
#define IRRECEIVER_HPP

#include "hwlib.hpp"

namespace target = hwlib::target;

class IrReceiver
{
private:
    uint16_t signal = 0;
    uint8_t player  = 0;
    uint8_t data    = 0;
    uint8_t control = 0;
public:
    IrReceiver(uint8_t player, uint8_t data):
    player(player),
    data(data)
    {}

    void test() {
        auto receiverData = target::pin_in( target::pins::d8 );
        auto receiverGround    = target::pin_out( target::pins::d9 );
        auto receiverVcc    = target::pin_out( target::pins::d10 );
        receiverGround.set( 0 );
        receiverVcc.set( 1 );

        auto startReceiving = hwlib::now_us();
        bool receivingIr = false;
        int delay = 0;
        int count = 0;
        for(;;){
            
            if( receiverData.get() == 0 && receivingIr == false ){
                receivingIr = true;
                startReceiving = hwlib::now_us();
            }
			if( receiverData.get() == 1 && receivingIr == true ){
                receivingIr = false;
                delay = ( hwlib::now_us() - startReceiving );
                if( delay > 600 && delay < 1000 ){
                    hwlib::cout << "0";
                }
                else if( delay > 1400 && delay < 1800 ){
                    hwlib::cout << "1";
                }
                if (count >= 16) {
                    hwlib::cout << hwlib::endl;
                    count = 0;
                }
				count++;
            }
			
        }
    }
};


#endif // IRRECEIVER_HPP