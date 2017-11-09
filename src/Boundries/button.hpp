#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "hwlib.hpp"

class Button {
private:
    hwlib::pin_in& buttonInput;
public:
    Button(hwlib::pin_in& buttonInput):
        buttonInput(buttonInput)
    {};

    auto get() {
        return (!buttonInput.get());
    };
};

#endif // BUTTON_HPP
