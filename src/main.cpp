#include "hwlib.hpp"
#include "irSender.hpp"

int main() {
	WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms( 500 );
    
    IrSender sender(1, 14);
    auto sw = hwlib::target::pin_in( hwlib::target::pins::d43 );
    auto sw2 = hwlib::target::pin_in( hwlib::target::pins::d44 );


    // when the switch is pressed, 
    // repeat sending 1 ms signal and 1 ms silence
    // and show this on the LED
	sender.send();
    for(;;) {
		sender.send();
		hwlib::wait_ms(100);
        if( !sw.get() ){
            sender.sendZero();
        }
        else if( !sw2.get() ){
            sender.sendOne();
        }
        
    }

    
    
	return 0;
}