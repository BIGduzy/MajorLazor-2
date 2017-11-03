#include "oledDisplayTask.hpp"

void OledDisplayTask::main() {
    while(true){
        auto data = oledChannel.read();
        display.dataPlaystate(data.time, data.lives, data.power, data.playerId);
    }
}

void OledDisplayTask::setDisplay(uint8_t time, uint8_t playerId, uint8_t lives, uint8_t power) {
    auto data = displayData(time, playerId, lives, power);
    oledChannel.write(data);
}