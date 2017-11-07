#ifndef IRRECEIVER_HPP
#define IRRECEIVER_HPP

#include "hwlib.hpp"

class IrReceiver {
private:
    hwlib::pin_in& dataPin;
    hwlib::pin_out& groundPin;
    hwlib::pin_out& vccPin;
    
public:
    /**
     * @brief Constructor
     * @param dataPin Hwlib pin in for the data
     * @param groundPin Hwlib pin out for the ground
     * @param vcc Hwlib pin out for the vcc
     */
    IrReceiver(hwlib::pin_in& dataPin, hwlib::pin_out& groundPin, hwlib::pin_out& vccPin):
        dataPin(dataPin),
        groundPin(groundPin),
        vccPin(vccPin)
    {
        groundPin.set(0);
        vccPin.set(1); 
    };

    /**
     * @brief returns value of dataPin
     */
    bool get() {
        return dataPin.get();
    };
};

#endif // IRRECEIVER_HPP
