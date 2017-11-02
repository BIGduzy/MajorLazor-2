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
    IrWeaponTask():
        task("IrWeaponTask"),
        fireButtonFlag(this, "fireButtonFlag")
    {};

    void main() override;
    void fireSet();
};

#endif // IRWEAPONTASK_HPP
