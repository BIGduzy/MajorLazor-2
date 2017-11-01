#ifndef PLAYERTASK_HPP
#define PLAYERTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>
#include "oledDiplayTask.hpp"

// NOTE: Maybe more to own file
struct Messagee {
    uint8_t playerId;
    uint8_t commandId;
    uint8_t data;

    Messagee() {}

    Messagee(uint8_t playerId, uint8_t commandId, uint8_t data):
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
};

class PlayerTask: public rtos::task<> {
private:
    enum States { INITIAL_STATE, PLAY_STATE, DONE_STATE };
    States state = INITIAL_STATE;

    OledDisplayTask& display;
    rtos::channel<Messagee, 5> messageChannel;
    uint8_t timeTillStart;
    Player player;

public:
    PlayerTask(OledDisplayTask& display);

    void main() override;

    // State functions
    void initialState();
    void playState();
    void doneState();

    // Interface functions
    void setMessage(uint8_t playerId, uint8_t commandId, uint8_t data);

    // Intern functions
    void setId(uint8_t data);
    void setDamage(uint8_t data);
    void setLives(uint8_t data);
};

#endif // PLAYERTASK_HPP
