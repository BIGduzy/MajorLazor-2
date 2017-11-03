#ifndef IRDETECTASK_HPP
#define IRDETECTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>

#include "irReceiver.hpp"
#include "irSignal.hpp"
#include "playerTask.hpp"

class IrDetecTask : public rtos::task<> {
private:
    PlayerTask& playerTask;
    IrReceiver irReceiver;
    IrSignal irSignal;

    rtos::clock ten_us_clock;

public:
    IrDetecTask(
        PlayerTask& playerTask,
        hwlib::pin_in& dataPin,
        hwlib::pin_out& groundPin,
        hwlib::pin_out& vccPin
    );

    void main() override;
    
};

#endif // IRDETECTASK_HPP
