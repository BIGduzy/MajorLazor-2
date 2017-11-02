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

/*
* Interface functions
*/

void PlayerTask::setMessage(uint8_t playerId, bool commandId, uint8_t data) {
    auto message = Message(playerId, commandId, data);
    messageChannel.write(message);
}

/*
* State functions
*/

void PlayerTask::initialState() {
    hwlib::cout << "Initial state" << hwlib::endl;

    // TODO: Do we need to use a wait here?
    auto message = messageChannel.read();

    while(message.playerId == 0 || message.commandId != 0 || message.data != 0) {
        // 00000-0nnnn-xxxxx to set the time
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
    
    // TODO: Write to pool

    state = PLAY_STATE;
}

void PlayerTask::playState() {
    hwlib::cout << "Play state" << hwlib::endl;

    // TODO: Remove me
    for(int i = 0; i < 8; i++) {
        display.write(i);
    }
    hwlib::wait_ms(1000);

    // TODO: Use clock and not intergers for timer
    while (player.lives > 0 && gameTimer < gameTime) {
        // TODO: is this how you wait on a channel?
        auto evt = wait(messageChannel);
        auto message = messageChannel.read();

        // If message is not from player its a damage hit
        if (message.playerId != 0) {
            doDamage(message);
        }
    }

    state = DONE_STATE;
}

void PlayerTask::doneState() {
    hwlib::cout << "Done state" << hwlib::endl;

    // TODO: Send to pc
    // Wait for connection
    // Send data
    state = INITIAL_STATE;
}

/*
* Intern functions
*/

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

void PlayerTask::doDamage(const Message& message) {
    // Damage the player
    setLives(player.lives - message.data);
    // Remember who damaged the player and what the damage was
    player.hitsBy[player.hitsByCounter] = message.playerId;
    player.hitsDamage[player.hitsByCounter] = message.data;
    ++player.hitsByCounter;
}