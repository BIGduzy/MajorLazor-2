#include <hwlib.hpp>
#include <rtos.hpp>

#include "keypadTask.hpp"
#include "command.hpp"

void KeypadTask::main() {
    for(;;) {
        if(keypad.char_available()) {
            keyPressed(keypad.getc());
        }
        
        wait(hundred_ms_clock);
    }
}

void KeypadTask::keyPressed(char c){
    //hwlib::cout << "Key: " << c << hwlib::endl;
    validInput = true;
    send = false;
    if(c == 'C') { // Clear all
        commandId = 0;
        commandSet = false;
        value = 0;
        valueSet = false;
    }
    else if(c == '#') { // End command
        if(!valueSet && value != 0) {
            valueSet = true;
        }
        else if(valueSet) {
            send = true;
        }
        else {
            validInput = false;
        }
    }
    else if(c == '*') { // Start game command
        commandId = 1; // ZET NAAR JUISTE COMMAND ID
        commandSet = true;
        value = 0;
        valueSet = true;
    }
    else if(c == 'A') { // Send command ID
        if(!commandSet && commandId != 0) {
            commandSet = true;
        }
        else {
            validInput = false;
        }
    }
    else if(c != 'B' && c != 'D') { // Numbers
        if(!commandSet) {
            commandId *= 10;
            commandId += (c-48);
        }
        else if(!valueSet) {
            value *= 10;
            value += (c-48);
        }
        else {
            validInput = false;
        }
    }
    else { // Invalid input
        validInput = false;
    }
    Command command(validInput, commandId, value, send);
    // TODO: Send via channel
    hwlib::cout << "ValidInput: " << command.validInput << " CommandId: " << command.commandId << " Value: " << command.value << " Send: " << command.send << hwlib::endl;
}
