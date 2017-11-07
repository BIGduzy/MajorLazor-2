#include "irWeaponTask.hpp"
#include "buttonTask.hpp"
#include "speakerTask.hpp"

void ButtonTask::main() {
    while(true) {
        wait(clock);
        if(fireButton.get()) {
            //Makes a beep
            speakerTask.setShootingFlag();
            
            irWeaponTask.fireSet();
            playerTask.setFlag();
        }
    }
}