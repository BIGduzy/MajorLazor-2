#ifndef PLAYERTASK_HPP
#define PLAYERTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>
#include "oledDisplayTask.hpp"
#include "message.hpp"

// TODO: Move to player.hpp
struct Player {
    uint8_t id;
    uint8_t damage;
    int8_t lives;

    // ohter stuff...
    uint8_t hitsBy[200];
    uint8_t hitsDamage[200];
    uint8_t hitsByCounter = 0;
};

class PlayerTask: public rtos::task<> {
private:
    enum States { INITIAL_STATE, PLAY_STATE, DONE_STATE };
    States state = INITIAL_STATE;

    Player player;
    OledDisplayTask& display;

    rtos::channel<Message, 5> messageChannel;
    rtos::timer gameTimer;

    uint8_t timeTillStart = 0; // Time in seconds
    unsigned long gameTime = 60 * 1000 * 1000; // 1 minute (timer in micro sec)

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
