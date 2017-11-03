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
    speaker.startSpeaker();
    beepTimer.set(2 * 1000 * 1000);
    wait(beepTimer);
    speaker.stopSpeaker();
}

void SpeakerTask::shootingState() {
    speaker.startSpeaker();
    beepTimer.set(1 * 1000 * 1000);
    wait(beepTimer);
    speaker.stopSpeaker();
}
