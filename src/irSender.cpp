#include "hwlib.hpp"
#include "irSender.hpp"

void IrSender::send_signal(){
    for( int i = 15; i >= 0; --i) {
        //hwlib::cout << ((signal >> i) & 1);
        if ((signal >> i) & 1) {
            sendOne();
        } else {
            sendZero();
        }
    }
    //hwlib::cout << hwlib::endl;
}

void IrSender::sendOne() {
    irLed.set(1);
    hwlib::wait_us(1600);//Vervang met rtos!
    irLed.set(0);
    hwlib::wait_us(800);
}

void IrSender::sendZero() {
    irLed.set(1);
    hwlib::wait_us(800);//Vervang met rtos!
    irLed.set(0);
    hwlib::wait_us(1600);
}

uint16_t IrSender::generateSignal(uint8_t player, uint8_t data) {
    uint16_t signal = 0;
    signal |= 1 << 15;
    signal |= player << 10;
    signal |= data << 5;
    signal |= player ^ data; // Control XOR
    
    return signal;
}

void IrSender::send() {
    signal = generateSignal(player, data);
    send_signal();
    hwlib::wait_ms(3); //Vervang met rtos!
    send_signal();
    hwlib::wait_ms(4);
}