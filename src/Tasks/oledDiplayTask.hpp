#ifndef IROLEDDISPLAYTASK_HPP
#define IROLEDDISPLAYTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class OledDisplayTask: public rtos::task<> {
public:
    IrOledDisplayTask():
        task("OledDisplayTask")
    {}

    void main() override;
}

#endif // IROLEDDISPLAYTASK_HPP
