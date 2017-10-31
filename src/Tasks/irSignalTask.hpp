#ifndef IRSIGNALTASK_HPP
#define IRSIGNALTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class IrPlayerTask: public rtos::task<> {
public:
    IrPlayerTask():
        task("IrPlayerTask")
    {}

    void main() override;
}

#endif // IRSIGNALTASK_HPP
