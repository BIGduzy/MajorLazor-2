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
        while(true){
            //hwlib::cout << "test1";
            for(int i = 0; i < 8; i++){
                display.write(i);
            }
            hwlib::wait_ms(1000);
            
        }
    }
};

#endif // PLAYERTASK_HPP
