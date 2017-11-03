#include <hwlib.hpp>
#include <rtos.hpp>

#include "irDetecTask.hpp"
#include "irSender.hpp"
#include "playerTask.hpp"
#include "tmp.hpp"
#include "oledDisplayTask.hpp"

#include "irReceiver.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );
    
    IrSender sender(5, 24);
    
    //IrReceiver receiver(1, 1);
    
    OledDisplayTask oledDisplay;
    
    //PlayerTask test(oledDisplay);
    //TmpTask tmp(test);
    
    oledDisplay.setDisplay(123, 12, 13, 14);
        
    rtos::run();

    return 0;
}