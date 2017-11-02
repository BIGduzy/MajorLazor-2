#ifndef IRDETECTASK_HPP
#define IRDETECTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "irReceiver.hpp"
#include "playerTask.hpp"

class IrDetecTask : public rtos::task<> {
private:
    PlayerTask& player;
    IrReceiver& receiver;

    uint8_t playerId  = 0;
    uint8_t data      = 0;

public:
    IrDetecTask(PlayerTask& player, IrReceiver& receiver, uint8_t playerId, uint8_t data):
        task("IrDetecTask"),
        player(player),
        receiver(receiver),
        playerId(playerId),
        data(data)
    {}

    void main() override {
        for(;;){
            hwlib::cout << "Test";
            receiver.test();
            hwlib::wait_ms(1000);
        }
    };
    
};

#endif // IRDETECTASK_HPP
