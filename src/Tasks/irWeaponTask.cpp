#include "irWeaponTask.hpp"

void IrWeaponTask::main() {
    for (;;) {
        switch(state) {
            case IDLE_STATE:
                break;
            case SEND_STATE:
                break;
        }
    }
}

void IrWeaponTask::idleState() {
    auto evt = wait(fireButtonFlag);
    state = SEND_STATE;
}

void IrWeaponTask::sendState() {
    weaponMutex.wait();
    auto w = weaponInfoPool.read();
    irSender.send(irSignal.encode(w.playerId, w.commandId, w.data));
    weaponMutex.signal();
    
    state = IDLE_STATE;
}

void IrWeaponTask::writeToPool(Message poolMessage) {
    weaponMutex.wait();
    weaponInfoPool.write(poolMessage);
    weaponMutex.signal();
}

void IrWeaponTask::startShooting() {
    fireButtonFlag.set();
}
