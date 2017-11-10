#include "irDetecTask.hpp"

IrDetecTask::IrDetecTask(
    PlayerTask& playerTask,
    SpeakerTask& speakerTask,
    hwlib::pin_in& dataPin,
    hwlib::pin_out& groundPin,
    hwlib::pin_out& vccPin
):
    task(0, "IrDetecTask"),
    playerTask(playerTask),
    speakerTask(speakerTask),
    irReceiver(dataPin, groundPin, vccPin),
    irDetecClock(this, 100, "irDetecClock"),
    irDetecTimer(this, "irDetecTimer")
{}

void IrDetecTask::main() {
    int count = 15;
    uint16_t signal1 = 0, signal2 = 0;
    bool checking = false;

    while(true) {
        auto evt = wait(irDetecClock);

        if(irReceiver.get() == 0) {
            hwlib::wait_us(1200);
            irDetecTimer.set(1200);

            bool b = !irReceiver.get();
            if (!checking) {
                signal1 |= b << count;
            } else {
                signal2 |= b << count;
            }
            --count;
            

            if (count < 0) {
                count = 15;

                if (!checking) {
                    checking = true;
                } else {
                    // Check if the 2 signals are the same
                    if (signal1 == signal2) {
                        // decode signal and check if it was correct
                        auto decodedSignal = irSignal.decode(signal1);
                        if (decodedSignal.correctData) {
                            playerTask.setMessage(
                                decodedSignal.playerId,
                                decodedSignal.commandId,
                                decodedSignal.data
                            );
                            speakerTask.setHitFlag();
                        } else {
                            hwlib::cout << "Signal corrupted" << hwlib::endl;
                            for (int i = 15; i >= 0; --i) {
                                hwlib::cout << int((signal1 >> i) & 0x01);
                            }
                            hwlib::cout << hwlib::endl;
                        }
                    } else {
                        hwlib::cout << "Invalid signal" << hwlib::endl;
                        hwlib::cout << (int)signal1 << hwlib::endl;
                        hwlib::cout << (int)signal2 << hwlib::endl<< hwlib::endl;
                    }

                    signal1 = 0;
                    signal2 = 0;
                    checking = false;
                }
            }
            wait(irDetecTimer); // Wait the remainig us of the 1200us timer
        }
    }
}