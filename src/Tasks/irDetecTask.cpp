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
    ten_us_clock(this, 10, "Ten us clock")
{}

void IrDetecTask::main() {
    auto startReceiving = hwlib::now_us();
    bool receivingIr = false;
    int delay = 0;
    int count = 15;
    uint16_t signal1 = 0, signal2 = 0;
    bool checking = false;

    while(true) {
        if(irReceiver.get() == 0 && receivingIr == false) {
            receivingIr = true;
            startReceiving = hwlib::now_us();
        }
        
        if(hwlib::now_us() - startReceiving > 4000) { // Misschien aanpassen zodat het niet blijft setten?
            count = 15;
        }
  
        if(irReceiver.get() == 1 && receivingIr == true) {
            receivingIr = false;
            delay = (hwlib::now_us() - startReceiving);

            if(delay > 600 && delay < 1000){
                if (!checking) {
                    signal1 |= 0x00 << count;
                } else {
                    signal2 |= 0x00 << count;
                }
                count--;
            } else if(delay > 1400 && delay < 1800) {
                if (!checking) {
                    signal1 |= 0x01 << count;
                } else {
                    signal2 |= 0x01 << count;
                }
                count--;
            }

            if (count < 0) {
                if (!checking) {
                    checking = true;
                    continue;
                }

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
                    }
                } else {
                    hwlib::cout << "Invalid signal" << hwlib::endl;
                    hwlib::cout << (int)signal1 << hwlib::endl;
                    hwlib::cout << (int)signal2 << hwlib::endl<< hwlib::endl;
                }

                count = 15;
                signal1 = 0;
                signal2 = 0;
                checking = false;
            }
        }

        wait(ten_us_clock);
    }
}