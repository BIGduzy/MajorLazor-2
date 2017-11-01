#ifndef PLAYERTASK_HPP
#define PLAYERTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "oledDiplayTask.hpp"

class PlayerTask: public rtos::task<> {
private:
    OledDisplayTask& display;
public:
    PlayerTask(OledDisplayTask& display):
        task("IrPlayerTask"),
        display(display)
    {}

    void main() override {
        for(;;){
            hwlib::wait_ms(10000);
        }
    }
};

#endif // PLAYERTASK_HPP
