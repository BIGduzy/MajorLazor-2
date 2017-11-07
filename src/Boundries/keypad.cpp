#include <hwlib.hpp>

#include "keypad.hpp"

char Keypad::pressed() {
    return keypad.pressed();
}

bool Keypad::char_available() {
    return keypad.char_available();
}

char Keypad::getc() {
    return keypad.getc();
}