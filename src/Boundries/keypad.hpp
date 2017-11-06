#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include <hwlib.hpp>

class Keypad {
private:
    hwlib::target::pin_in& row0;
    hwlib::target::pin_in& row1;
    hwlib::target::pin_in& row2;
    hwlib::target::pin_in& row3;
    hwlib::target::pin_oc& col0;
    hwlib::target::pin_oc& col1;
    hwlib::target::pin_oc& col2;
    hwlib::target::pin_oc& col3;
    
    // Make ports for keypad
    hwlib::port_oc_from_pins colPort = hwlib::port_oc_from_pins(col0, col1, col2, col3);
    hwlib::port_in_from_pins rowPort = hwlib::port_in_from_pins(row0, row1, row2, row3);
    // Make matrix for keypad
    hwlib::matrix_of_switches matrix = hwlib::matrix_of_switches(colPort, rowPort);
    // Make keypad
    hwlib::keypad< 16 > keypad = hwlib::keypad< 16 >(matrix, "123A456B789C*0#D");
public:
    Keypad(
    hwlib::target::pin_in row0,
    hwlib::target::pin_in row1,
    hwlib::target::pin_in row2,
    hwlib::target::pin_in row3,
    hwlib::target::pin_oc col0,
    hwlib::target::pin_oc col1,
    hwlib::target::pin_oc col2,
    hwlib::target::pin_oc col3):
        row0(row0),
        row1(row1),
        row2(row2),
        row3(row3),
        col0(col0),
        col1(col1),
        col2(col2),
        col3(col3)
    {}
    
    char pressed();
    
    bool char_available();
    
    char getc();
};

#endif // KEYPAD_HPP
