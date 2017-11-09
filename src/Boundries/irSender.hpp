#ifndef IRSENDER_HPP
#define IRSENDER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

namespace target = hwlib::target;

class IrSender {
  private:
    // uint16_t signal = 0; //0: Startbit(1), 1-5: Speler(1-31), 6-10:
    // Data(0-31), 11-15: Controlebits(11 XOR van 1 & 6, 12 XOR van 2 & 7 etc.)
    // uint8_t player  = 0;
    // uint8_t data    = 0;
    // uint8_t control = 0;

    target::d2_36kHz irLed = target::d2_36kHz();

    /**
     * @brief Function to physically send the signal.
     */
    void send_signal(uint16_t signal);
    /**
     * @brief Function which sends a one over IR.
     */
    void sendOne();
    /**
     * @brief Function which sends a zero over IR.
     */
    void sendZero();
    // uint16_t generateSignal(uint8_t player, uint8_t data);
  public:
    /**
     * @brief Constructor.
     */
    IrSender() {};

    /**
     * @brief Main function for sending a signal.
     * @param singal[in] The encoded message to be send.
     */
    void send(uint16_t signal);
};

#endif // IRSENDER_HPP
