#ifndef IRSIGNALTASK_HPP
#define IRSIGNALTASK_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "playerTask.hpp"
#include "irWeaponTask.hpp"

class IrSignalTask: public rtos::task<> {
private:
    rtos::flag fireButtonFlag;
    rtos::pool<int> weaponInfoPool;
    rtos::mutex mutexForWeaponInfoPool;
    rtos::channel<uint16_t, 10> messageChannel;
    
    PlayerTask& playerTask;
    IrWeaponTask& irWeaponTask;

    auto decode(uint16_t encodedMessage);
    auto encode(uint8_t playerId, uint8_t data);
public:
    IrSignalTask(PlayerTask& playerTask, IrWeaponTask& irWeaponTask):
        task("IrSignalTask"),
        fireButtonFlag(this, "fireButtonFlag"),
        weaponInfoPool("weaponInfoPool"),
        mutexForWeaponInfoPool("mutexForWeaponInfoPool"),
        messageChannel(this, "messageChannel"),
        playerTask(playerTask),
        irWeaponTask(irWeaponTask)
    {}

    void main() override;
};

#endif // IRSIGNALTASK_HPP
