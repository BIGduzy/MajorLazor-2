#ifndef IRSIGNAL_HPP
#define IRSIGNAL_HPP

#include "hwlib.hpp"
#include "playerTask.hpp"

class irSignal {
private:
public:
    irSignal();

    auto encode(uint8_t playerId, uint8_t data) {
        auto signal = 0;
        signal |= 1 << 15;
        signal |= playerId << 10;
        signal |= data << 5;
        signal |= playerId ^ data;
        return signal;
    }

    void decode(uint16_t message) {
        setMessage((message >> 10) & 0x1F, (message >> 9) & 0x01, (message >> 5) & 0xF);
    }
}

#endif // IRSIGNAL_HPP
