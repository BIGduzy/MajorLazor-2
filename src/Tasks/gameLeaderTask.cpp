#include "gameLeaderTask.hpp"

GameLeaderTask::GameLeaderTask(IrWeaponTask& irWeaponTask, OledDisplayTask& display):
    task("ButtonTask"),
    irWeaponTask(irWeaponTask),
    display(display),
    messageChannel(this, "messageChannel"),
    commandChannel(this, "commandChannel")
{}

void GameLeaderTask::main() {
    hwlib::cout << "Game leader" << hwlib::endl;
    while(true) {
        auto evt = wait(commandChannel + messageChannel);

        if (evt == commandChannel) {
            auto command = commandChannel.read();
            
            // Display command to oled
            display.setDisplay(command);

            // Send data to weapon
            if (command.send) {
                switch(command.commandId) {
                    case 0: // Set time
                        irWeaponTask.writeToPool(Message(0, 0, command.value));
                        break;
                    case 1: // Start game
                        irWeaponTask.writeToPool(Message(0, 0, 0 ));
                    default: // Other commands
                        // Tell player what field we want to edit
                        // We do commandId - 2 because the commands start at 0
                        irWeaponTask.writeToPool(Message(0, 1, command.commandId - 2 ));
                        irWeaponTask.startShooting();
                        // Set field value
                        irWeaponTask.writeToPool(Message(0, 1, command.value ));
                }

                irWeaponTask.startShooting();
            }
        }
    }
}

void GameLeaderTask::addCommand(const Command& command) {
    commandChannel.write(command);
}