#ifndef OLEDDISPLAY_HPP
#define OLEDDISPLAY_HPP

#include "hwlib.hpp"

namespace target = hwlib::target;

class OledDisplay {
private:
   target::pin_oc scl = target::pin_oc( target::pins::scl );
   target::pin_oc sda = target::pin_oc( target::pins::sda );
   
   hwlib::i2c_bus_bit_banged_scl_sda i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   
   hwlib::glcd_oled display = hwlib::glcd_oled( i2c_bus, 0x3c );


public:
    OledDisplay(target::pin_oc scl, target::pin_oc sda, hwlib::i2c_bus_bit_banged_scl_sda i2c_bus, hwlib::glcd_oled display):
        scl(scl),
        sda(sda),
        i2c_bus(i2c_bus),
        display(display)
    {
        display.clear();
    }

    void clear(bool flush = false);
};

#endif // OLEDDISPLAY_HPP
