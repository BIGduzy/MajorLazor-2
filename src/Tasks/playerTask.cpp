#include "playerTask.hpp"

PlayerTask::PlayerTask(OledDisplayTask& display):
    task("IrPlayerTask"),
    display(display),
    messageChannel(this, "messageChannel"),
    gameTimer(this, "gameTimer")
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
    // hwlib::cout << "ID: " << (int)playerId << " Command: " << (int)commandId << " Data: " << (int)data << hwlib::endl << hwlib::endl;
    auto message = Message(playerId, commandId, data);
    messageChannel.write(message);
}

/*
* State functions
*/

void PlayerTask::initialState() {
    hwlib::cout << "Initial state" << hwlib::endl;

    // TODO: wait for fire flag
    // wait(fireButtonFlag);


    auto evt = wait(messageChannel);
    auto message = messageChannel.read();
    
    while(message.commandId != 0 || message.data != 0) {
        if (message.playerId != 0) continue; // Skip non gameleader messages

        // 00000-0nnnn-xxxxx to set the time
        if (message.commandId == 0) {
            timeTillStart = message.data;
            hwlib::cout << "Time till start: " << (int)timeTillStart << hwlib::endl;
        } else {
            // hwlib::cout << "Command ID: " << (int)message.data << hwlib::endl;
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
        // Get new message
        evt = wait(messageChannel);
        message = messageChannel.read();
    }
    
    // TODO: Write to pool

    hwlib::cout << "Time to start: " << (int)timeTillStart << hwlib::endl;

    state = PLAY_STATE;
}

void PlayerTask::playState() {
    hwlib::cout << "Play state" << hwlib::endl;

    gameTimer.set(timeTillStart * 1000 * 1000); // * 1000'000 to convert to microsecs
    wait(gameTimer);

    hwlib::cout << "Game start!" << hwlib::endl;

    gameTimer.set(gameTime);
    while (player.lives > 0) {
        auto evt = wait(messageChannel + gameTimer);
        if (evt == gameTimer) {
            // Game time over
            hwlib::cout << "Time up!" << hwlib::endl;
            break;
        }

        auto message = messageChannel.read();

        // If message is from a player other than yourself its a damage hit
        if (message.playerId != 0 && message.playerId != player.id) {
            doDamage(message);
            hwlib::cout << "Lives left: " << (int)player.lives << hwlib::endl;
        }
    }

    // TODO: Display gameover on display
    hwlib::cout << "Game over!" << hwlib::endl;

    state = DONE_STATE;
}

void PlayerTask::doneState() {
    hwlib::cout << "Done state" << hwlib::endl << hwlib::endl;

    hwlib::cout << "Hit by: " << hwlib::endl;
    for (uint8_t i = 0; i < player.hitsByCounter; ++i) {
        auto hitDamage = player.hitsDamage[i];
        auto hitBy = player.hitsBy[i];

        hwlib::cout << (int)hitBy << " -- " << (int)hitDamage << hwlib::endl;
    }

    // TODO: Send to pc
    // Wait for connection
    while(true) {}
    // Send data
    state = INITIAL_STATE;
}

/*
* Intern functions
*/

void PlayerTask::setId(uint8_t data) {
    player.id = data;
    hwlib::cout << "id: " << (int)player.id << hwlib::endl;
}

void PlayerTask::setDamage(uint8_t data) {
    player.damage = data;
    hwlib::cout << "damage: " << (int)player.damage << hwlib::endl;
}

void PlayerTask::setLives(uint8_t data) {
    player.lives = data;
    hwlib::cout << "lives: " << (int)player.lives << hwlib::endl;
}

void PlayerTask::doDamage(const Message& message) {
    // Damage the player
    setLives(player.lives - message.data);
    // Remember who damaged the player and what the damage was
    player.hitsBy[player.hitsByCounter] = message.playerId;
    player.hitsDamage[player.hitsByCounter] = message.data;
    ++player.hitsByCounter;
}