#ifndef OLEDDISPLAYTASK_HPP
#define OLEDDISPLAYTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>

#include "oledDisplay.hpp"

struct displayData {
    uint8_t time;
    uint8_t playerId;
    uint8_t lives;
    uint8_t power;
    
    displayData() {}
    
    displayData(uint8_t time, uint8_t playerId, uint8_t lives, uint8_t power):
        time(time),
        playerId(playerId),
        lives(lives),
        /*kills(kills),  //To implement later
        streak(streak),*/
        power(power)
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
    
    void setDisplay(uint8_t time, uint8_t playerId, uint8_t lives, uint8_t power);
};

#endif // OLEDDISPLAYTASK_HPP
