#ifndef OLEDDISPLAYTASK_HPP
#define OLEDDISPLAYTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>

#include "oledDisplay.hpp"

struct displayData {
    uint8_t time     = 0;
    uint8_t playerId = 0;
    uint8_t lives    = 0;
    uint8_t power    = 0;
    
    //int state;
    
    enum States { INITIAL_STATE, PLAY_STATE, DONE_STATE };
    States state;
    
    displayData(uint8_t time):
        time(time),
        state(INITIAL_STATE)
        //state(0)
    {}
    
    displayData(uint8_t time, uint8_t playerId, uint8_t lives, uint8_t power):
        time(time),
        playerId(playerId),
        lives(lives),
        /*kills(kills),  //To implement later
        streak(streak),*/
        power(power),
        state(PLAY_STATE)
        //state(1)
    {}
    
    displayData():
        state(DONE_STATE)
        //state(2)
    {}  
};

class OledDisplayTask: public rtos::task<> {
    rtos::channel<displayData, 5> oledChannel;
    
    OledDisplay display;
public:
    OledDisplayTask():
        task("OledDisplayTask"),
        oledChannel(this, "oledChannel")
    {}

    void main() override;
    
    void setDisplay(uint8_t time);
    void setDisplay(uint8_t time, uint8_t playerId, uint8_t lives, uint8_t power);
    void setDisplay();
};

#endif // OLEDDISPLAYTASK_HPP
