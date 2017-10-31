#ifndef OLEDDISPLAYTASK_HPP
#define OLEDDISPLAYTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class OledDisplayTask: public rtos::task<> {
    rtos::channel<int, 5> naampie;
public:
    OledDisplayTask():
        task("OledDisplayTask"),
        naampie(this, "naampie")
    {}

    void main() override {
        while(true){
            //hwlib::cout << "test2";
            int i = naampie.read();
            hwlib::cout << i;
        }
    }
    
    void write(int i) {
        naampie.write(i);
    }
    
};

#endif // OLEDDISPLAYTASK_HPP
