#include "hwlib.hpp"
#include "irSender.hpp"

int main() {
	WDT->WDT_MR = WDT_MR_WDDIS;
	
    
    IrSender sender(1, 14);
    auto sw = hwlib::target::pin_in( hwlib::target::pins::d43 );
    auto sw2 = hwlib::target::pin_in( hwlib::target::pins::d44 );


    // when the switch is pressed, 
    // repeat sending 1 ms signal and 1 ms silence
    // and show this on the LED
    for(;;) {
        hwlib::wait_ms( 1 ); 


        if( !sw.get() ){
            hwlib::wait_ms(1);
            sender.sendOne();
        }
        else if( !sw2.get() ){
            hwlib::wait_ms(2);
            sender.sendZero();
        }
        
    }

    
    
	return 0;
}