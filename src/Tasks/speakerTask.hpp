#ifndef SPEAKERTASK_HPP
#define SPEAKERTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "speaker.hpp"

class SpeakerTask: public rtos::task<> {
private:
    /*enum States = { IDLE_STATE, HIT_STATE, SHOOTING_STATE };
    States state = IDLE_STATE;*/
    enum States { IDLE_STATE, HIT_STATE, SHOOTING_STATE };
    States state = IDLE_STATE;

    rtos::timer beepTimer;
    rtos::flag hitFlag;
    rtos::flag firingFlag;

    Speaker speaker;

    void idleState();
    void hitState();
    void shootingState();

public:
    SpeakerTask(hwlib::pin_out& lsp);

    void main() override;

    void setHitFlag() {
        hitFlag.set();
    }
    
    void setShootingFlag() {
        firingFlag.set();
    }
};

#endif // SPEAKERTASK_HPP
