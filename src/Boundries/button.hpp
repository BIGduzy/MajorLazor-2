#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "hwlib.hpp"

namespace target = hwlib::target;

class Button {
private:
    target::pin_in buttonInput = target::pin_in(target::pins::d7);
public:
    Button();

    auto get() {
        return (!buttonInput.get());
    };
};

#endif // BUTTON_HPP
