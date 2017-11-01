#ifndef IRDETECTASK_HPP
#define IRDETECTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "irReceiver.hpp"
#include "playerTask.hpp"

class IrDetecTask: public rtos::task<> {
private:
    PlayerTask& player;

    uint8_t playerId  = 0;
    uint8_t data    = 0;

public:
    IrDetecTask(PlayerTask& player, uint8_t playerId, uint8_t data):
        task("IrDetecTask"),
        player(player),
        playerId(playerId),
        data(data)
    {
        IrReceiver receiver(playerId, data);
    }

    void main() override {};
};

#endif // IRDETECTASK_HPP
