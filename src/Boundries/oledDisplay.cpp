#include "hwlib.hpp"
#include "oledDisplay.hpp"

void OledDisplay::clear(bool flush) {
    display.clear();
    if(flush){
        display.flush();
    }
}