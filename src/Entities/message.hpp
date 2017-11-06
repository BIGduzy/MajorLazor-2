#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <hwlib.hpp>

// NOTE: Maybe move to own file
struct Message {
    uint8_t playerId;
    bool commandId;
    uint8_t data;
    bool correctData;

    /**
     * @brief Default constructor
     */
    Message() {}

    /**
     * @brief Constructor
     * @param playerId The id of the player
     * @param commandId The id of the commandId
     * @param data The data
     */
    Message(uint8_t playerId, bool commandId, uint8_t data):
        playerId(playerId),
        commandId(commandId),
        data(data),
        correctData(false)
    {}
};

#endif // MESSAGE_HPP