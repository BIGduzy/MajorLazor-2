#ifndef IRWEAPONTASK_HPP
#define IRWEAPONTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "irSender.hpp"

class IrWeaponTask: public rtos::task<> {
public:
    IrWeaponTask():
        task("IrWeaponTask")
    {}

    void main() override;
};

#endif // IRWEAPONTASK_HPP
