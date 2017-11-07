#include "speakerTask.hpp"

SpeakerTask::SpeakerTask(hwlib::pin_out& lsp):
    task("SpeakerTask"),
    beepTimer(this, "BeepTimer"),
    hitFlag(this, "HitFlag"),
    firingFlag(this, "FiringFlag"),
    speaker(lsp)
{}

void SpeakerTask::main() {
    for (;;) {
        switch(state) {
            case IDLE_STATE:
                idleState();
                break;
            case HIT_STATE:
                hitState();
                break;
            case SHOOTING_STATE:
                shootingState();
                break;
            default:
                hwlib::cout << "Fatal Error" << hwlib::endl;
                break;
        }
    }
}

void SpeakerTask::idleState() {
    auto event = wait(hitFlag + firingFlag);
    if (event == hitFlag) {
        state = HIT_STATE;
    } else {
        state = SHOOTING_STATE;
    }
}

void SpeakerTask::hitState() {
    // Loop for two seconds
    auto start_time = hwlib::now_us();

    while(2000000 > (hwlib::now_us() - start_time) ) {
        //Turn on the speaker
        speaker.startSpeaker();
        beepTimer.set(500);
        wait(beepTimer);
    
        //Turn off the speaker
        speaker.stopSpeaker();
        beepTimer.set(500);
        wait(beepTimer);
    }
    
    state = IDLE_STATE;
}

void SpeakerTask::shootingState() {
    
    // Loop for two seconds
    auto start_time = hwlib::now_us();
    while(1000000 > (hwlib::now_us() - start_time) ) {

        //Turn on the speaker
        speaker.startSpeaker();
        beepTimer.set(800);
        wait(beepTimer);
    
        //Turn off the speaker
        speaker.stopSpeaker();
        beepTimer.set(800);
        wait(beepTimer);
    }

    state = IDLE_STATE;
}
