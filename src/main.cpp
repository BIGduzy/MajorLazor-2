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
#include "buttonTask.hpp"
#include "speakerTask.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms( 500 );

    OledDisplayTask oledDisplay;
    IrWeaponTask irWeaponTask;

    constexpr const bool ROLE = 0; // 0 = gameLeader / 1 = player

    // ROLE variations
    if (ROLE == 0) {
        // GameLeader
        GameLeaderTask gameLeaderTask(irWeaponTask, oledDisplay);

        // Setup necessary items for the keypad
        auto in0  = hwlib::target::pin_in(hwlib::target::pins::a3);
        auto in1  = hwlib::target::pin_in(hwlib::target::pins::a2);
        auto in2  = hwlib::target::pin_in(hwlib::target::pins::a1);
        auto in3  = hwlib::target::pin_in(hwlib::target::pins::a0);
        auto out0 = hwlib::target::pin_oc(hwlib::target::pins::a7);
        auto out1 = hwlib::target::pin_oc(hwlib::target::pins::a6);
        auto out2 = hwlib::target::pin_oc(hwlib::target::pins::a5);
        auto out3 = hwlib::target::pin_oc(hwlib::target::pins::a4);
        auto outPort = hwlib::port_oc_from_pins(out0, out1, out2, out3);
        auto inPort = hwlib::port_in_from_pins(in0, in1, in2, in3);
        auto matrix = hwlib::matrix_of_switches(outPort, inPort);
        auto keypad = hwlib::keypad<16>(matrix, "123A456B789C*0#D");
        KeypadTask keypadTask(gameLeaderTask, keypad);
        
        // Startup rtos
        rtos::run();
    } else if (ROLE == 1) {
        // Player
        PlayerTask playerTask(irWeaponTask, oledDisplay);

        //Speaker Stuff ~
        auto lsp_pin = hwlib::target::pin_out( hwlib::target::pins::d8 );
        SpeakerTask speakerTask(lsp_pin);
        speakerTask.setShootingFlag();
        
        // Fire button
        auto buttonPin = hwlib::target::pin_in(hwlib::target::pins::d7);
        Button button(buttonPin);
        ButtonTask buttonTask(irWeaponTask, playerTask, speakerTask, button);
        
        // Detector
        auto dataPin   = hwlib::target::pin_in(hwlib::target::pins::a8);
        auto groundPin = hwlib::target::pin_out(hwlib::target::pins::a9);
        auto vccPin    = hwlib::target::pin_out(hwlib::target::pins::a10);
        IrDetecTask irDetecTask(playerTask, speakerTask, dataPin, groundPin, vccPin);
        
        // Startup rtos
        rtos::run();
    }

    return 0;
}