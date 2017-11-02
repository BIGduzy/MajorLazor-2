#ifndef IRRECEIVER_HPP
#define IRRECEIVER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

namespace target = hwlib::target;

class IrReceiver : public rtos::task<> {
private:
    uint16_t signal = 0;
    uint8_t player  = 0;
    uint8_t data    = 0;
    uint8_t control = 0;
    
    rtos::clock ten_us_clock;
    
public:
    IrReceiver(uint8_t player, uint8_t data):
        task("Ir Receiver"),
        player(player),
        data(data),
        ten_us_clock(this, 10, "Ten us clock")
    {}

    void main() override;
    
    void test() { hwlib::cout << data; };
};

#endif // IRRECEIVER_HPP
