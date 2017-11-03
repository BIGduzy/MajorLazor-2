#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <hwlib.hpp>

// NOTE: Maybe move to own file
struct Message {
    uint8_t playerId;
    bool commandId;
    uint8_t data;
    bool correctData;

    Message() {}

    Message(uint8_t playerId, bool commandId, uint8_t data):
        playerId(playerId),
        commandId(commandId),
        data(data),
        correctData(false)
    {}
};

#endif // MESSAGE_HPP