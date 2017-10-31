#ifndef IRPLAYERTASK_HPP
#define IRPLAYERTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class IrPlayerTask: public rtos::task<> {
private:
    rtos::channel<int, 5> naampie;
public:
    IrPlayerTask():
        task("IrPlayerTask"),
        naampie(this, "naampie")
    {}

    void main() override;
}

#endif // IRPLAYERTASK_HPP
