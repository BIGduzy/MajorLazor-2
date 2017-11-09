#include "playerTask.hpp"

PlayerTask::PlayerTask(IrWeaponTask& irWeaponTask, OledDisplayTask& display):
    task(0, "IrPlayerTask"),
    irWeaponTask(irWeaponTask),
    display(display),
    fireButtonFlag(this, "fireButtonFlag"),
    messageChannel(this, "messageChannel"),
    gameTimer(this, "gameTimer")
{}

void PlayerTask::main() {
    hwlib::cout << "Player" << hwlib::endl;
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

void PlayerTask::setFlag() {
    fireButtonFlag.set();
}

/*
* State functions
*/

void PlayerTask::initialState() {
    hwlib::cout << "Initial state" << hwlib::endl;

    // Wait for fire flag, so the gameleader knows which player to initialize
    wait(fireButtonFlag);
    hwlib::cout << "Ready for init" << hwlib::endl;
    messageChannel.clear(); // Clear unwanted data

    auto evt = wait(messageChannel);
    auto message = messageChannel.read();
    display.setDisplay(player.id, player.lives, player.damage, timeTillStart, (gameTime / 1000 / 1000));
    
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
        display.setDisplay(player.id, player.lives, player.damage, timeTillStart, (gameTime / 1000 / 1000));
    }
    
    // Write weapon info to pool
    irWeaponTask.writeToPool({player.id, 1, player.damage});

    // Wait for fire flag, to start the game
    fireButtonFlag.clear();
    hwlib::cout << "Press the fire button to start" << hwlib::endl;
    wait(fireButtonFlag);
    
    hwlib::cout << "Time to start: " << (int)timeTillStart << hwlib::endl;

    //TODO: Display countdown

    state = PLAY_STATE;
}

void PlayerTask::playState() {
    hwlib::cout << "Play state" << hwlib::endl;

    gameTimer.set(timeTillStart * 1000 * 1000); // * 1000'000 to convert to microsecs
    wait(gameTimer);

    hwlib::cout << "Game start!" << hwlib::endl;

    uint64_t startTime = hwlib::now_us();

    gameTimer.set(gameTime);
    while (player.lives > 0) {
        auto evt = wait(messageChannel + gameTimer + fireButtonFlag);
        if (evt == gameTimer) {
            // Game time over
            hwlib::cout << "Time up!" << hwlib::endl;
            break;
        } else if (evt == messageChannel) {
            // Got hit!
            auto message = messageChannel.read();

            // If message is from a player other than yourself its a damage hit
            if (message.playerId != 0 && message.playerId != player.id) {
                doDamage(message);
                hwlib::cout << "Lives left: " << (int)player.lives << hwlib::endl;
            }
        } else if (evt == fireButtonFlag) {
            // Fire!
            hwlib::cout << "Piew!" << hwlib::endl;
            irWeaponTask.startShooting();
        }

        uint64_t newTime = hwlib::now_us();
        uint64_t timeDiff = (newTime - startTime);
        uint8_t timeLeft = (gameTime - timeDiff) / 1'000'000;

        hwlib::cout << "Time: " << (int)timeLeft << hwlib::endl;

        // Display data
        // TODO: Time left only gets updated when the channel has a message
        display.setDisplay(timeLeft, player.id, player.lives, player.damage);
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
    while(true) {
        gameTimer.set(1000 * 1000); // Wait 1 sec
        wait(gameTimer);
        hwlib::cout << "Waiting for connection..." << hwlib::endl;

        // Display gameover
        display.setDisplay();
    }
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