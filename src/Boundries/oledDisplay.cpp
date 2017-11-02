#include "hwlib.hpp"
#include "oledDisplay.hpp"

void oledDisplay::clear(bool flush) {
    display.clear();
    if(flush){
        display.flush();
    }
}