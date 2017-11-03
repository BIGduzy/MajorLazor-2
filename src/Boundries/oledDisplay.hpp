#ifndef OLEDDISPLAY_HPP
#define OLEDDISPLAY_HPP

#include <hwlib.hpp>

#include "due-twi.hpp"

namespace target = hwlib::target;

class OledDisplay {
private:

    target::twi_bus_due twi_bus;

    hwlib::glcd_oled display = hwlib::glcd_oled( twi_bus, 0x3c );

    hwlib::font_default_8x8 font = hwlib::font_default_8x8();
    hwlib::window_ostream displayOstream = hwlib::window_ostream( display, font );


    

public:
    OledDisplay()
    {
        clear();
        layoutPlaystate();
    }

    void layoutInitialstate();
    void layoutPlaystate();
    void layoutDonestate();
    
    void dataInitialstate();
    void dataPlaystate(int time, int playerId, int lives, int power);
    void dataDonestate();

    void clear(bool flush = false);
};

#endif // OLEDDISPLAY_HPP
