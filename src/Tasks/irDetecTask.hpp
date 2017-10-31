#ifndef IRDETECTASK_HPP
#define IRDETECTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "irReceiver.hpp"

class IrDetecTask: public rtos::task<> {
public:
    IrDetecTask():
        task("IrDetecTask")
    {}

    void main() override;
}

#endif // IRDETECTASK_HPP
