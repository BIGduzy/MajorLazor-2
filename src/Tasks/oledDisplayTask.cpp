#include "oledDisplayTask.hpp"

void OledDisplayTask::main() {
    while(true){
        auto data = oledChannel.read();
        display.dataDisplay(data.playerId, data.lives, data.power, data.time);
    }
}

void OledDisplayTask::setDisplay(uint8_t playerId, uint8_t lives, uint8_t power, uint8_t time) {
    auto data = displayData(playerId, lives, power, time);
    oledChannel.write(data);
}