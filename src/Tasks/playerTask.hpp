#ifndef PLAYERTASK_HPP
#define PLAYERTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>
#include "oledDiplayTask.hpp"

// NOTE: Maybe move to own file
struct Message {
    uint8_t playerId;
    bool commandId;
    uint8_t data;

    Message() {}

    Message(uint8_t playerId, bool commandId, uint8_t data):
        playerId(playerId),
        commandId(commandId),
        data(data)
    {}
};

// TODO: Move to player.hpp
struct Player {
    uint8_t id;
    uint8_t damage;
    uint8_t lives;

    // ohter stuff...
    uint8_t hitsBy[200];
    uint8_t hitsDamage[200];
    uint8_t hitsByCounter = 0;
};

class PlayerTask: public rtos::task<> {
private:
    enum States { INITIAL_STATE, PLAY_STATE, DONE_STATE };
    States state = INITIAL_STATE;

    OledDisplayTask& display;
    rtos::channel<Message, 5> messageChannel;
    uint8_t timeTillStart;
    uint16_t gameTimer = 0;
    uint16_t gameTime = 300;
    Player player;

public:
    PlayerTask(OledDisplayTask& display);

    void main() override;

    // Interface functions
    void setMessage(uint8_t playerId, bool commandId, uint8_t data);

private:
    // State functions
    void initialState();
    void playState();
    void doneState();

    // Intern functions
    void setId(uint8_t data);
    void setDamage(uint8_t data);
    void setLives(uint8_t data);
    void doDamage(const Message& message);
};

#endif // PLAYERTASK_HPP
