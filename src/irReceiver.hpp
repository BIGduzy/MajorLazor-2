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
    IrReceiver:
    {}

    void test() {
        auto receiverData = target::pin_in( target::pins::d8 );
        auto receiverGround    = target::pin_out( target::pins::d9 );
        auto receiverVcc    = target::pin_out( target::pins::d10 );
        receiverGround.set( 0 );
        receiverVcc.set( 1 );

        auto startReceiving = hwlib::now_us();
        bool receivingIr = false
        for(;;){
            if( receiverData.get() == 0 && receivingIr == false ){
                receivingIr = true;
                startReceiving = hwlib::now_us();
            }
			if( receiverData.get() == 1 && receivingIr == true ){
                receivingIr = false;
				hwlib::cout << ( hwlib::now_us() - startReceiving );
            }
			
        }
    }
};


#endif // IRRECEIVER_HPP