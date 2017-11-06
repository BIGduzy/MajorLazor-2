#include <hwlib.hpp>
#include <rtos.hpp>

#include "irDetecTask.hpp"
#include "irSender.hpp"
#include "playerTask.hpp"
#include "tmp.hpp"
#include "oledDisplayTask.hpp"
#include "keypadTask.hpp"
#include "keypad.hpp"
#include "irReceiver.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );
    
    IrSender sender(5, 24);
    
    OledDisplayTask oledDisplay;
    PlayerTask playerTask(oledDisplay);
    TmpTask tmp(playerTask);

    
    auto receiverData   = hwlib::target::pin_in(hwlib::target::pins::d8);
    auto receiverGround = hwlib::target::pin_out(hwlib::target::pins::d9);
    auto receiverVcc    = hwlib::target::pin_out(hwlib::target::pins::d10);

    IrDetecTask IrDetecTask(
        playerTask,
        receiverData,
        receiverGround,
        receiverVcc
    );
    
    Keypad keypad(
    hwlib::target::pin_in( hwlib::target::pins::d46 ),
    hwlib::target::pin_in( hwlib::target::pins::d48 ),
    hwlib::target::pin_in( hwlib::target::pins::d50 ),
    hwlib::target::pin_in( hwlib::target::pins::d52 ),
    hwlib::target::pin_oc( hwlib::target::pins::d38 ),
    hwlib::target::pin_oc( hwlib::target::pins::d40 ),
    hwlib::target::pin_oc( hwlib::target::pins::d42 ),
    hwlib::target::pin_oc( hwlib::target::pins::d44 )
    );
    
    KeypadTask keypadTask(keypad);

    rtos::run();

    return 0;
}