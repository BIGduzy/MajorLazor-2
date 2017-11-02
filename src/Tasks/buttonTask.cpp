#include "irWeaponTask.hpp"
#include "buttonTask.hpp"

void ButtonTask::main() {
    for(;;) {
        switch(state) {
            case IDLE_STATE:
                idleState();
                break;
            case CHECKING_STATE:
                checkingState();
                break;
        }
    }
}

void ButtonTask::idleState() {
    hwlib::wait_ms(1);
    state = CHECKING_STATE;
}

void ButtonTask::checkingState() {
    if(fireButton.get()) {
        irWeaponTask.fireSet();
    }
}
