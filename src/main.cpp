#include "hwlib.hpp"
#include "rtos.hpp"

#include "irDetecTask.hpp"
#include "irSender.hpp"
#include "playerTask.hpp"
#include "oledDiplayTask.hpp"


int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );
    
    OledDisplayTask oledTest;

    PlayerTask test(oledTest);
        
    IrDetecTask detector(test, 1, 14);
 
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