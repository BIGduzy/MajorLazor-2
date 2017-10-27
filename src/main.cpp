#include "hwlib.hpp"
#include "irReceiver.hpp"
#include "irSender.hpp"
#include "rtos.hpp"


int main() { //Main receiver
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );
    
    IrReceiver receiver(1, 14);
    
    rtos::run();

    return 0;
}


/*
int main() { //Main sender
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );
    
    IrSender sender(5, 24);
    auto sw = hwlib::target::pin_in( hwlib::target::pins::d43 );
    auto sw2 = hwlib::target::pin_in( hwlib::target::pins::d44 );


    for(;;) {
        sender.send();
        hwlib::wait_ms(1000);
    }

    return 0;
}
*/