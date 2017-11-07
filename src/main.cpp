#include <hwlib.hpp>
#include <rtos.hpp>

#include "irDetecTask.hpp"
#include "gameLeaderTask.hpp"
#include "oledDisplayTask.hpp"
#include "irWeaponTask.hpp"
#include "keypadTask.hpp"
#include "keypad.hpp"
#include "irReceiver.hpp"
#include "button.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );
    
    IrWeaponTask irWeaponTask;

    OledDisplayTask oledDisplay;
    GameLeaderTask gameLeaderTask(irWeaponTask, oledDisplay);

    // auto receiverData   = hwlib::target::pin_in(hwlib::target::pins::d8);
    // auto receiverGround = hwlib::target::pin_out(hwlib::target::pins::d9);
    // auto receiverVcc    = hwlib::target::pin_out(hwlib::target::pins::d10);
    // IrDetecTask IrDetecTask(
    //    playerTask,
    //    receiverData,
    //    receiverGround,
    //    receiverVcc
    // );

    auto in0  = hwlib::target::pin_in(hwlib::target::pins::a3);
	auto in1  = hwlib::target::pin_in(hwlib::target::pins::a2);
	auto in2  = hwlib::target::pin_in(hwlib::target::pins::a1);
	auto in3  = hwlib::target::pin_in(hwlib::target::pins::a0);
	auto out0 = hwlib::target::pin_oc(hwlib::target::pins::a7);
	auto out1 = hwlib::target::pin_oc(hwlib::target::pins::a6);
	auto out2 = hwlib::target::pin_oc(hwlib::target::pins::a5);
    auto out3 = hwlib::target::pin_oc(hwlib::target::pins::a4);
	// Setup necessary items for the keypad
	auto outPort = hwlib::port_oc_from_pins(out0, out1, out2, out3);
	auto inPort = hwlib::port_in_from_pins(in0, in1, in2, in3);
	auto matrix = hwlib::matrix_of_switches(outPort, inPort);
	auto keypad = hwlib::keypad<16>(matrix, "123A456B789C*0#D");

    KeypadTask keypadTask(gameLeaderTask, keypad);

    // Startup rtos
    rtos::run();

    return 0;
}