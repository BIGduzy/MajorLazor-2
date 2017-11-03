#ifndef IRRECEIVER_HPP
#define IRRECEIVER_HPP

#include "hwlib.hpp"

class IrReceiver {
private:
    hwlib::pin_in& dataPin;
    hwlib::pin_out& groundPin;
    hwlib::pin_out& vccPin;
    
public:
    IrReceiver(hwlib::pin_in& dataPin, hwlib::pin_out& groundPin, hwlib::pin_out& vccPin):
        dataPin(dataPin),
        groundPin(groundPin),
        vccPin(vccPin)
    {
        groundPin.set(0);
        vccPin.set(1);
        
    };

<<<<<<< HEAD
    void main() override;
    
    void test() { hwlib::cout << data; };
=======
    bool get() {
        return dataPin.get();
    };
>>>>>>> IrDetecTask
};

#endif // IRRECEIVER_HPP
