#ifndef IRWEAPONTASK_HPP
#define IRWEAPONTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "irSignal.hpp"
#include "irSender.hpp"
#include "message.hpp"

class IrWeaponTask: public rtos::task<> {
private:
    rtos::pool<Message> weaponInfoPool;
    rtos::mutex weaponMutex;
    rtos::flag fireButtonFlag;
    enum States {IDLE_STATE, SEND_STATE};
    States state = IDLE_STATE;

    IrSender irSender;
    IrSignal irSignal;

    /**
     * @brief Function representing the idle state.
     */
    void idleState();
    /**
     * @brief Function representing the sending state.
     */
    void sendState();

public:
    /**
     * @brief Constructor
     */
    IrWeaponTask():
        task(2, "IrWeaponTask"),
        weaponInfoPool("weaponInfoPool"),
        weaponMutex("weaponMutex"),
        fireButtonFlag(this, "fireButtonFlag")
    {}

    /**
    * @brief rtos main override
    *
    * @details
    * Rtos main function that runs the task
    */
    void main() override;

    /**
     * @brief Function for writing the current weaponInfo to the pool.
     * @param poolMessage[in] Message struct containing weaponInfo.
     */
    void writeToPool(Message poolMessage);
    /**
     * @brief Start shooting using the current weaponInfo.
     */
    void startShooting();
};

#endif // IRWEAPONTASK_HPP
