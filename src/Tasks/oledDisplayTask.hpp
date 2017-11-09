#ifndef OLEDDISPLAYTASK_HPP
#define OLEDDISPLAYTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>

#include "oledDisplay.hpp"
#include "command.hpp"

struct displayData {
    uint8_t time      = 0;
    uint8_t playerId  = 0;
    uint8_t lives     = 0;
    uint8_t damage    = 0;
    uint8_t power     = 0;
    uint8_t startTime = 0;
    uint8_t gameTime  = 0;

    bool validInput = false;
    int commandId = 0;
    int value = 0;
    bool send = false;
    
    enum States { INITIAL_STATE, PLAY_STATE, DONE_STATE, LEADER_STATE };
    States state;
    
    displayData(uint8_t playerId, uint8_t lives, uint8_t damage, uint8_t startTime, uint8_t gameTime):
        playerId(playerId),
        lives(lives),
        damage(damage),
        startTime(startTime),
        gameTime(gameTime),
        state(INITIAL_STATE)
    {}
    
    displayData(uint8_t time, uint8_t playerId, uint8_t lives, uint8_t damage):
        time(time),
        playerId(playerId),
        lives(lives),
        /*kills(kills),  //To implement later
        streak(streak),*/
        damage(damage),
        state(PLAY_STATE)
    {}
    
    displayData():
        state(DONE_STATE)
    {}
    
    displayData(bool validInput, int commandId, int value, bool send):
        validInput(validInput),
        commandId(commandId),
        value(value),
        send(send),
        state(LEADER_STATE)
    {}

};

class OledDisplayTask: public rtos::task<> {
    rtos::channel<displayData, 5> oledChannel;
    
    OledDisplay display;
public:
    OledDisplayTask():
        task(4, "OledDisplayTask"),
        oledChannel(this, "oledChannel")
    {
        display.clear(true);
    }

    void main() override;
    
    void setDisplay(uint8_t id, uint8_t lives, uint8_t damage, uint8_t startTime, uint8_t gameTime);
    void setDisplay(uint8_t time, uint8_t playerId, uint8_t lives, uint8_t damage);
    void setDisplay();
    void setDisplay(const Command& command);
};

#endif // OLEDDISPLAYTASK_HPP
