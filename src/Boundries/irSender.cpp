#include "hwlib.hpp"
#include "irSender.hpp"

void IrSender::send_signal(uint16_t signal) {
    for (int i = 15; i >= 0; --i) {
        if ((signal >> i) & 1) {
            sendOne();
        } else {
            sendZero();
        }
    }
}

void IrSender::sendOne() {
    irLed.set(1);
    hwlib::wait_us_busy(1600);
    irLed.set(0);
    hwlib::wait_us_busy(800);
}

void IrSender::sendZero() {
    irLed.set(1);
    hwlib::wait_us_busy(800);
    irLed.set(0);
    hwlib::wait_us_busy(1600);
}

// uint16_t IrSender::generateSignal(uint8_t player, uint8_t data) {
//    uint16_t signal = 0;
//    signal |= 1 << 15;
//    signal |= player << 10;
//    signal |= data << 5;
//    signal |= player ^ data; // Control XOR
//
//    return signal;
//}

void IrSender::send(uint16_t signal) {
    send_signal(signal);
    hwlib::wait_ms(3); // Vervang met rtos!
    send_signal(signal);
    hwlib::wait_ms(4);
}
