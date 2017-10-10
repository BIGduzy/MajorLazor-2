#ifndef IRSENDER_HPP
#define IRSENDER_HPP

#include "hwlib.hpp"

class IrSender
{
private:
    uint16_t signal = 0;
    uint8_t player  = 0;
    uint8_t data    = 0;
    uint8_t control = 0;
    
    namespace target = hwlib::target
    
    auto irLed = target::pins::d2_36kHz;
public:
    IrSender(uint8_t player, uint8_t data):
    player(player),
    data(data)
    {}
    
    void sendOne() {
        irLed.set(1);
        hwlib::wait_us(1600);
        irLed.set(0);
        hwlib::wait_us(800);
    }
    
    void sendZero() {
        irLed.set(1);
        hwlib::wait_us(800);
        irLed.set(0);
        hwlib::wait_us(1600);
    }
    
    uint16_t generateSignal(uint8_t player, uint8_t data) {
        uint16_t signal = 0;
        signal |= 1 << 15;
        signal |= player << 10;
        signal |= data << 5;
        signal |= player ^ data; // Control XOR
        
        return signal;
    }
    
    void send() {
        signal = generateSignal(player, data);
        for(uint16_t i = 15; i >= 0; --i) {
            if ((signal >> i) & 1) {
                sendOne();
            } else {
                sendZero();
            }
        }
    }
}

#endif // IRSENDER_HPP