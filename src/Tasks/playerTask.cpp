#include "playerTask.hpp"

PlayerTask::PlayerTask(OledDisplayTask& display):
    task("IrPlayerTask"),
    display(display),
    messageChannel(this, "messageChannel")
{}

void PlayerTask::main() {
    while(true) {
        switch(state) {
            case INITIAL_STATE:
                initialState();
                break;
            case PLAY_STATE:
                playState();
                break;
            case DONE_STATE:
                doneState();
                break;
            default:
                hwlib::cout << "FATAL ERROR" << hwlib::endl;
                while(true) {}
                break;
        }
    }
}

// State functions

void PlayerTask::initialState() {
    hwlib::cout << "Initial state" << hwlib::endl;

    while(true) {
        auto message = messageChannel.read();

        while(message.playerId == 0 || message.commandId != 0 || message.data != 0) {
            if (message.commandId == 0) {
                timeTillStart = message.data;
            } else {
                switch(message.data) {
                    case 0:
                        // Set id
                        wait(messageChannel); // TODO: timeout
                        message = messageChannel.read();
                        setId(message.data);
                        break;
                    case 1:
                        // Set damage
                        wait(messageChannel); // TODO: timeout
                        message = messageChannel.read();
                        setDamage(message.data);
                        break;
                    case 2:
                        // Set lives
                        wait(messageChannel); // TODO: timeout
                        message = messageChannel.read();
                        setLives(message.data);
                        break;
                }
            }
        }
    }

    state = PLAY_STATE;
}

void PlayerTask::playState() {
    hwlib::cout << "Play state" << hwlib::endl;
    for(int i = 0; i < 8; i++) {
        display.write(i);
    }
    hwlib::wait_ms(1000);
}

void PlayerTask::doneState() {
    hwlib::cout << "Done state" << hwlib::endl;
}

// Interface functions

void PlayerTask::setMessage(uint8_t playerId, uint8_t commandId, uint8_t data) {
    auto messagee = Messagee(playerId, commandId, data);
    messageChannel.write(messagee);
}

// Intern functions

void PlayerTask::setId(uint8_t data) {
    player.id = data;
    hwlib::cout << player.id << hwlib::endl;
}

void PlayerTask::setDamage(uint8_t data) {
    player.damage = data;
    hwlib::cout << player.damage << hwlib::endl;
}

void PlayerTask::setLives(uint8_t data) {
    player.lives = data;
    hwlib::cout << player.lives << hwlib::endl;
}