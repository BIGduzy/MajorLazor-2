#include "keypadTask.hpp"

KeypadTask::KeypadTask(GameLeaderTask& gameLeaderTask, hwlib::keypad<16>& keypad):
    task(1, "KeypadTask"),
    gameLeaderTask(gameLeaderTask),
    hundred_ms_clock(this, 100'000, "100 ms clock"),
    keypad(keypad)
{}

void KeypadTask::main() {
    while(true) {
        if(keypad.char_available()) {
            keyPressed(keypad.getc());
        }
        
        wait(hundred_ms_clock);
    }
}

void KeypadTask::keyPressed(char c){
    // hwlib::cout << "Key: " << c << hwlib::endl;
    validInput = true;
    send = false;
    if(c == 'C') { // Clear all
        commandId = 0;
        commandSet = false;
        value = 0;
        valueSet = false;
    }
    else if(c == '#') { // End command
        if(!valueSet) {
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
        if(!commandSet) {
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
    gameLeaderTask.addCommand(command);
    hwlib::cout << "ValidInput: " << command.validInput << " CommandId: " << command.commandId << " Value: " << command.value << " Send: " << command.send << hwlib::endl;
}
