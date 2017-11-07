#include "oledDisplayTask.hpp"

void OledDisplayTask::main() {
    while(true){
        auto data = oledChannel.read();
        switch(data.state) {
            case data.INITIAL_STATE:
                display.clear();
                display.layoutInitialstate();
                display.dataInitialstate(data.time);
                break;
            case data.PLAY_STATE:
                display.clear();
                display.layoutPlaystate();
                display.dataPlaystate(data.time, data.lives, data.power, data.playerId);
                break;
            case data.DONE_STATE:
                display.clear();
                display.layoutDonestate();
                //display.dataDonestate();
                break;
            case data.LEADER_STATE:
                display.clear();
                display.layoutLeaderstate();
                display.dataLeaderstate(data.validInput, data.commandId, data.value, data.send);
        }
    }
}

void OledDisplayTask::setDisplay(uint8_t time) { // Data for initial state
    auto data = displayData(time);
    oledChannel.write(data);
}

void OledDisplayTask::setDisplay(uint8_t time, uint8_t playerId, uint8_t lives, uint8_t power) { // Data for play state
    auto data = displayData(time, playerId, lives, power);
    oledChannel.write(data);
}

void OledDisplayTask::setDisplay() { // Data for done state
    auto data = displayData();
    oledChannel.write(data);
}

void OledDisplayTask::setDisplay(Command command) {
    auto data = displayData(command.validInput, command.commandId, command.value, command.send);
    oledChannel.write(data);
}