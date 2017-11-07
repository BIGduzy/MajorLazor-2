#ifndef KEYPADTASK_HPP
#define KEYPADTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>

#include "command.hpp"
//#include "keypad.hpp"   Legacy

class KeypadTask : public rtos::task<> {
private:
    rtos::clock hundred_ms_clock;

    hwlib::keypad< 16 > keypad;
    
    bool validInput;
    
    int commandId   = 0;
    bool commandSet = false;
    int value       = 0;
    bool valueSet   = false;
    bool send       = false;

    //Keypad& keypad;   Legacy

public:
    KeypadTask( hwlib::keypad<16>& keypad):
        task("KeypadTask"),
        hundred_ms_clock(this, 100000, "100 ms clock"),
        keypad(keypad)
    {}

    void main() override;
    
    void keyPressed(char c);
    
};

#endif // KEYPADTASK_HPP
