#include "irWeaponTask.hpp"
#include "buttonTask.hpp"
#include "speakerTask.hpp"

void ButtonTask::main() {
    while(true) {
        wait(clock);
        if(fireButton.get()) {
            //
            speakerTask.setShootingFlag();
            //
            irWeaponTask.fireSet();
            playerTask.setFlag();
        }
    }
}