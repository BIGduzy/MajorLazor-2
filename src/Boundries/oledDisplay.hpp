#ifndef OLEDDISPLAY_HPP
#define OLEDDISPLAY_HPP

#include "hwlib.hpp"

namespace target = hwlib::target;

class OledDisplay {
private:
   target::pin_oc scl;
   target::pin_oc sda;
   
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   
    hwlib::glcd_oled display = hwlib::glcd_oled( i2c_bus, 0x3c );
   
    hwlib::font_default_8x8 font = hwlib::font_default_8x8();
    hwlib::window_ostream displayOstream = hwlib::window_ostream( display, font );


public:
    OledDisplay(target::pin_oc scl = target::pin_oc( target::pins::scl ), target::pin_oc sda = target::pin_oc( target::pins::sda )):
        scl(scl),
        sda(sda)
    {
        display.clear();
    }

    void clear(bool flush = false);
    
    void test(){
        displayOstream 
        << "\t0101" <<"ID:" << "\t0701" << "Lives:"
        << "\t0103" << "Kills:"
        << "\t0104" << "Power:"
        << "\t0106" << "Streak:"
        << hwlib::flush; 
        for(int i = 0; i < 128; i++){
            display.write( hwlib::location( i, 0 ), hwlib::black );
        }
        for(int i = 0; i < 128; i++){
            display.write( hwlib::location( i, 63 ), hwlib::black );
        }
        for(int i = 0; i < 64; i++){
            display.write( hwlib::location( 0, i ), hwlib::black );
        }
        for(int i = 0; i < 64; i++){
            display.write( hwlib::location( 127, i ), hwlib::black );
        }
        for(int i = 0; i < 128; i++){
            display.write( hwlib::location( i, 18 ), hwlib::black );
        }
        for(int i = 0; i < 128; i++){
            display.write( hwlib::location( i, 45), hwlib::black );
        }
    }
};

#endif // OLEDDISPLAY_HPP
