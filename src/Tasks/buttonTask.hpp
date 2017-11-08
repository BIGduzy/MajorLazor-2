#ifndef BUTTONTASK_HPP
#define BUTTONTASK_HPP

#include <rtos.hpp>
#include <hwlib.hpp>
#include "button.hpp"
#include "irWeaponTask.hpp"
#include "playerTask.hpp"
#include "speakerTask.hpp"

class ButtonTask: public rtos::task<> {
private:
    IrWeaponTask& irWeaponTask;
    PlayerTask& playerTask;
    SpeakerTask& speakerTask;
    Button& fireButton;

    rtos::clock clock;
public:
    /**
     * @brief Constructor
     */
    ButtonTask(IrWeaponTask& irWeaponTask, PlayerTask& playerTask, SpeakerTask& speakerTask, Button& fireButton): 
        task("ButtonTask"),
        irWeaponTask(irWeaponTask),
        playerTask(playerTask),
        speakerTask(speakerTask),
        fireButton(fireButton),
        clock(this, 1000)
    {};

    /**
    * @brief rtos main override
    *
    * @details
    * Rtos main function that runs the task
    */
    void main() override;
};

#endif // BUTTONTASK_HPP
