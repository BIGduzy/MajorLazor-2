#ifndef KEYPADTASK_HPP
#define KEYPADTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>

#include "keypad.hpp"

class KeypadTask : public rtos::task<> {
private:
    rtos::clock hundred_ms_clock;

    Keypad& keypad;

public:
    KeypadTask(Keypad& keypad):
        task("KeypadTask"),
        hundred_ms_clock(this, 100000, "100 ms clock"),
        keypad(keypad)
    {}

    void main() override
    {
        for(;;) {
            if(keypad.char_available()) {
                hwlib::cout << keypad.getc();
            }
            
            wait(hundred_ms_clock);
        }
    }
    
};

#endif // KEYPADTASK_HPP
