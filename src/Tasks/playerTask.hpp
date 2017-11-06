#ifndef PLAYERTASK_HPP
#define PLAYERTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>
#include "oledDisplayTask.hpp"
#include "message.hpp"

class PlayerTask: public rtos::task<> {
private:
    enum States { INITIAL_STATE, PLAY_STATE, DONE_STATE };
    States state = INITIAL_STATE;

    struct Player {
        uint8_t id;
        uint8_t damage;
        int8_t lives;
    
        // other stuff...
        uint8_t hitsBy[200];
        uint8_t hitsDamage[200];
        uint8_t hitsByCounter = 0;
    };
    Player player;
    OledDisplayTask& display;

    rtos::channel<Message, 5> messageChannel;
    rtos::timer gameTimer;

    uint8_t timeTillStart = 0; // Time in seconds
    unsigned long gameTime = 60 * 1000 * 1000; // 1 minute (timer in micro sec)

public:
    /**
    * @brief Constructor
    * @param display The task for the OledDisplay
    */
    PlayerTask(OledDisplayTask& display);

    /**
    * @brief rtos main override
    *
    * @details
    * Rtos main function that runs the task
    */
    void main() override;

    // *******************
    // Interface functions
    // *******************

    /** 
     * @brief Interface function to write to messageChannel
     * @param playerId the id of the player that send the message
     * @param commandId the id of the command
     * @param data the data that needs to be send
     * 
     * @details
     * Puts the variables in a struct and writes it to the channel
     */
    void setMessage(uint8_t playerId, bool commandId, uint8_t data);

private:
    // ***************
    // State functions
    // ***************

    /**
     * @brief Initial state
     * 
     * @details
     * Deals with all logic for the initial state,
     * see the Solution Architecture for more info
     */
    void initialState();
    /**
     * @brief Play state
     * 
     * @details
     * Deals with all logic for the play state,
     * see the Solution Architecture for more info
     */
    void playState();
    /**
     * @brief Done state
     * 
     * @details
     * Deals with all logic for the done state,
     * see the Solution Architecture for more info
     */
    void doneState();

    // ****************
    // Intern functions
    // ****************

    /**
     * @brief sets id for player
     * @param data New value for id
     */
    void setId(uint8_t data);
    /**
     * @brief sets damage for player
     * @param data New value for damage
     */
    void setDamage(uint8_t data);
    /**
     * @brief sets lives for player
     * @param data New value for lives
     */
    void setLives(uint8_t data);
    /**
     * @brief Deals damage to player
     * @param message Message entity with playerId of the player that did the damage,
     * and the damage in the data field
     * 
     * @details
     * Lowers lives of player with the setLives function,
     * then saves the damage and the playerId that did the damage in the player entity
     */
    void doDamage(const Message& message);
};

#endif // PLAYERTASK_HPP
