#ifndef KEYPADTASK_HPP
#define KEYPADTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>

#include "command.hpp"
#include "gameLeaderTask.hpp"
//#include "keypad.hpp"   Legacy

class KeypadTask : public rtos::task<> {
private:
    GameLeaderTask& gameLeaderTask;
    rtos::clock hundred_ms_clock;

    hwlib::keypad<16> keypad;
    
    bool validInput;
    
    int commandId   = 0;
    bool commandSet = false;
    int value       = 0;
    bool valueSet   = false;
    bool send       = false;

    //Keypad& keypad;   Legacy

public:
    KeypadTask(GameLeaderTask& gameLeaderTask, hwlib::keypad<16>& keypad);

    void main() override;
    
    void keyPressed(char c);
    
};

#endif // KEYPADTASK_HPP
