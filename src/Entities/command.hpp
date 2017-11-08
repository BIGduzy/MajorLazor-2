#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <hwlib.hpp>

struct Command {
    bool validInput;
    int commandId;
    int value;
    bool send;
    
    Command() {}
    
    Command(bool validInput, int commandId, int value, bool send):
        validInput(validInput),
        commandId(commandId),
        value(value),
        send(send)
    {}
    
};

#endif // COMMAND_HPP