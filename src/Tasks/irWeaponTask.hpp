#ifndef IRWEAPONTASK_HPP
#define IRWEAPONTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "irSender.hpp"

class IrWeaponTask: public rtos::task<> {
public:
    /**
     * @brief Constructor
     */
    IrWeaponTask():
        task("IrWeaponTask")
    {}

    /**
    * @brief rtos main override
    *
    * @details
    * Rtos main function that runs the task
    */
    void main() override;
};

#endif // IRWEAPONTASK_HPP
