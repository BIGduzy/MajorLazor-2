#include "irWeaponTask.hpp"

IrWeaponTask::IrWeaponTask():
    task("IrWeaponTask"),
    fireButtonFlag(this, "fireButtonFlag")
{}

void IrWeaponTask::main() {
    while(true) {
        hwlib::wait_ms(1000);
    }
}

void IrWeaponTask::fireSet() {
    fireButtonFlag.set();
}
