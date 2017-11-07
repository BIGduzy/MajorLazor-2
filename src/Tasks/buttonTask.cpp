#include "irWeaponTask.hpp"
#include "buttonTask.hpp"

void ButtonTask::main() {
    while(true) {
        wait(clock);
        if(fireButton.get()) {
            irWeaponTask.fireSet();
            playerTask.setFlag();
        }
    }
}