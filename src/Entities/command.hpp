#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <hwlib.hpp>

struct Command {
    bool validInput = false;
    int commandId = 0;
    int value = 0;
    bool send = false;
    
    Command() {}
    
    Command(bool validInput, int commandId = 0, int value = 0, bool send = false ):
        validInput(validInput),
        commandId(commandId),
        value(value),
        send(send)
    {}
    
};

#endif // COMMAND_HPP