#include "hwlib.hpp"
#include "rtos.hpp"

#include "irDetecTask.hpp"
#include "irSender.hpp"
#include "playerTask.hpp"
#include "tmp.hpp"
#include "oledDiplayTask.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );
    
    IrSender sender(5, 24);
    
    OledDisplayTask oledDisplay;
    PlayerTask test(oledDisplay);
    TmpTask tmp(test);

        
    rtos::run();

    return 0;
}