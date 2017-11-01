#include "hwlib.hpp"
#include "rtos.hpp"

#include "irDetecTask.hpp"
#include "irSender.hpp"
#include "playerTask.hpp"
#include "oledDiplayTask.hpp"


int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );
    
    IrSender sender(5, 24);
    
    OledDisplayTask oledTest;

    PlayerTask test(oledTest);
    
    IrReceiver receiver(1, 14);
    
    IrDetecTask detector(test, receiver, 1, 14);
 
    rtos::run();

    return 0;
}