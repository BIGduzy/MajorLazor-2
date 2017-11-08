#ifndef GAMELEADERTASK_HPP
#define GAMELEADERTASK_HPP

#include <rtos.hpp>
#include <hwlib.hpp>
#include "irWeaponTask.hpp"
#include "command.hpp"
#include "oledDisplayTask.hpp"

class GameLeaderTask: public rtos::task<> {
private:
    IrWeaponTask& irWeaponTask;
    OledDisplayTask& display;
    
    rtos::channel<Message, 5> messageChannel;
    rtos::channel<Command, 5> commandChannel;
public:
    /**
     * @brief Constructor
     */
    GameLeaderTask(IrWeaponTask& irWeaponTask, OledDisplayTask& display
    );

    /**
    * @brief rtos main override
    *
    * @details
    * Rtos main function that runs the task
    */
    void main() override;

    /**
     * @brief writes command to commandChannel
     */
    void addCommand(const Command& command);
};

#endif // GAMELEADERTASK_HPP