#ifndef IRSENDER_HPP
#define IRSENDER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

namespace target = hwlib::target;

class IrSender : public rtos::task<> {
private:
    uint16_t signal = 0; //0: Startbit(1), 1-5: Speler(1-31), 6-10: Data(0-31), 11-15: Controlebits(11 XOR van 1 & 6, 12 XOR van 2 & 7 etc.)
    uint8_t player  = 0;
    uint8_t data    = 0;
    uint8_t control = 0;
    
    target::d2_36kHz irLed = target::d2_36kHz();
    
    void send_signal();
public:
    IrSender(uint8_t player, uint8_t data):
        task("Ir Sender"),
        player(player),
        data(data)
    {}
    
    void main() override;
    
    void sendOne();
    void sendZero();
    uint16_t generateSignal(uint8_t player, uint8_t data);
    void send();
    
};

#endif // IRSENDER_HPP
