#ifndef IRSIGNAL_HPP
#define IRSIGNAL_HPP

#include <hwlib.hpp>
#include "message.hpp"

class IrSignal {
public:
    IrSignal() {};
    /**
     * @brief Encodes playerId, commandId and data to binary
     * @return 16 bit binary number:
     * 
     * |Bit         | Data                |
     * |------------|---------------------|
     * |0           | Start bit           |
     * |1 - 5       | PlayerId            |
     * |6           | commandId           |
     * |7 - 10      | data                |
     * |11 - 15     | Control bits        |
     */
    uint16_t encode(uint8_t playerId, bool commandBit, uint8_t data) {
        auto signal = 0;
        signal |= 1 << 15;
        signal |= playerId << 10;
        signal |= (int)commandBit << 9;
        signal |= data << 5;
        signal |= playerId ^ (data | (commandBit << 5));
        return signal;
    };

    /**
     * @brief Decodes binary to playerId, CommandId and data and puts it in a Message
     * @return Message entity, with playerId, commandId, data and if the data was  
     * correct in de correctData field 
     */
    Message decode(uint16_t message) {
        Message mes((message >> 10) & 0x1F, (message >> 9) & 0x01, (message >> 5) & 0xF);
        if(((message >> 10 & 0x1F) ^ (message >> 5 & 0x1F)) == (message & 0x1F)) {
            mes.correctData = true;
        }
        return mes;
    };
};

#endif // IRSIGNAL_HPP
