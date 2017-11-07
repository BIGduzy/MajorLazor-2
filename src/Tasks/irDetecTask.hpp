#ifndef IRDETECTASK_HPP
#define IRDETECTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>

#include "irReceiver.hpp"
#include "irSignal.hpp"
#include "playerTask.hpp"
#include "speakerTask.hpp"

class IrDetecTask : public rtos::task<> {
private:
    PlayerTask& playerTask;
    SpeakerTask& speakerTask;
    IrReceiver irReceiver;
    IrSignal irSignal;

    rtos::clock ten_us_clock;

public:
    /**
     * @brief Constructor
     * @param playerTask The playerTask, see Solution Architecture for more info
     * @param speakerTask The speakerTask, see Solution Architecture for more info
     * @param dataPin Hwlib pin in for the data of irReceiver
     * @param groundPin Hwlib pin out for the ground of irReceiver
     * @param vcc Hwlib pin out for the vcc of irReceiver
     */
    IrDetecTask(
        PlayerTask& playerTask,
        SpeakerTask& speakerTask,
        hwlib::pin_in& dataPin,
        hwlib::pin_out& groundPin,
        hwlib::pin_out& vccPin
    );

    /**
    * @brief rtos main override
    *
    * @details
    * Rtos main function that runs the task
    */
    void main() override;
    
};

#endif // IRDETECTASK_HPP
