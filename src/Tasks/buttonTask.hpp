#ifndef BUTTONTASK_HPP
#define BUTTONTASK_HPP

#include "button.hpp"
#include "irWeaponTask.hpp"

#include "rtos.hpp"
#include "hwlib.hpp"

class ButtonTask: public rtos::task<> {
private:
    enum States {IDLE_STATE, CHECKING_STATE};
    States state = IDLE_STATE;

    IrWeaponTask& irWeaponTask;
    Button& fireButton;

public:
    ButtonTask(IrWeaponTask& irWeaponTask, Button& fireButton): 
        task("ButtonTask"),
        irWeaponTask(irWeaponTask),
        fireButton(fireButton) 
    {};

    void main() override;
private:
    void idleState();
    void checkingState();
};

#endif // BUTTONTASK_HPP
