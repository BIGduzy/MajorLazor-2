#ifndef IRWEAPONTASK_HPP
#define IRWEAPONTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "irSender.hpp"

class IrWeaponTask: public rtos::task<> {
private:
    rtos::flag fireButtonFlag;

    enum States {IDLE_STATE, CHECKING_STATE};
    States state = IDLE_STATE;

public:
    /**
     * @brief Constructor
     */
    IrWeaponTask();

    /**
    * @brief rtos main override
    *
    * @details
    * Rtos main function that runs the task
    */
    void main() override;

    /**
     * @brief Sets fireButtonFlag
     */
    void fireSet();
};

#endif // IRWEAPONTASK_HPP
