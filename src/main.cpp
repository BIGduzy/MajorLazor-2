#include <hwlib.hpp>
#include <rtos.hpp>

#include "irDetecTask.hpp"
#include "irSender.hpp"
#include "playerTask.hpp"
#include "buttonTask.hpp"
#include "tmp.hpp"
#include "oledDisplayTask.hpp"
#include "irWeaponTask.hpp"
#include "keypadTask.hpp"
#include "keypad.hpp"
#include "irReceiver.hpp"
#include "button.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );
    
    IrSender sender(5, 24);
    IrWeaponTask irWeaponTask;

    OledDisplayTask oledDisplay;
    PlayerTask playerTask(oledDisplay);

    auto buttonPin = hwlib::target::pin_in(hwlib::target::pins::d7);
    Button button(buttonPin);
    ButtonTask buttonTask(irWeaponTask, playerTask, button);
    // TODO: Remove when gameLeader works
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
    
    
    // Make pins for keypad
    auto row0 = hwlib::target::pin_in(hwlib::target::pins::d46);
    auto row1 = hwlib::target::pin_in(hwlib::target::pins::d48);
    auto row2 = hwlib::target::pin_in(hwlib::target::pins::d50);
    auto row3 = hwlib::target::pin_in(hwlib::target::pins::d52);
    auto col0 = hwlib::target::pin_oc(hwlib::target::pins::d38);
    auto col1 = hwlib::target::pin_oc(hwlib::target::pins::d40);
    auto col2 = hwlib::target::pin_oc(hwlib::target::pins::d42);
    auto col3 = hwlib::target::pin_oc(hwlib::target::pins::d44);
    // Make ports for keypad
    hwlib::port_oc_from_pins colPort = hwlib::port_oc_from_pins(col0, col1, col2, col3);
    hwlib::port_in_from_pins rowPort = hwlib::port_in_from_pins(row0, row1, row2, row3);
    // Make matrix for keypad
    hwlib::matrix_of_switches matrix = hwlib::matrix_of_switches(colPort, rowPort);
    // Make keypad
    hwlib::keypad<16> keypad = hwlib::keypad< 16 >(matrix, "123A456B789C*0#D");
    KeypadTask keypadTask(keypad);

    // Startup rtos
    rtos::run();

    return 0;
}