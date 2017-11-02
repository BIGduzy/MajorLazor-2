#include "hwlib.hpp"
#include "rtos.hpp"

#include "irDetecTask.hpp"
#include "irSender.hpp"
#include "playerTask.hpp"
#include "oledDiplayTask.hpp"
#include "oledDispaly.hpp"


int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );
    
    IrSender sender(5, 24);
    
    OledDisplayTask oledDisplay;

    PlayerTask player(oledDisplay);
    
    IrReceiver receiver(1, 14);
    
    IrDetecTask detector(player, receiver, 1, 14);
    
    OledDisplay display();
 
    rtos::run();

    return 0;
}