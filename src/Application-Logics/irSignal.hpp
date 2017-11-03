#ifndef IRSIGNAL_HPP
#define IRSIGNAL_HPP

#include <hwlib.hpp>
#include "message.hpp"

class IrSignal {
public:
    uint16_t encode(uint8_t playerId, uint8_t data) {
        auto signal = 0;
        signal |= 1 << 15;
        signal |= playerId << 10;
        signal |= data << 5;
        signal |= playerId ^ data;
        return signal;
    };

    Message decode(uint16_t message) {
        Message mes((message >> 10) & 0x1F, (message >> 9) & 0x01, (message >> 5) & 0xF);
        if(((message >> 10 & 0x1F) ^ (message >> 5 & 0x1F)) == (message & 0x1F)) {
            mes.correctData = true;
        }
        return mes;
    };
};

#endif // IRSIGNAL_HPP