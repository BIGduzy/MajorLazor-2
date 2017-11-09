#ifndef TMPTASK_HPP
#define TMPTASK_HPP

#include <hwlib.hpp>
#include <rtos.hpp>
#include "playerTask.hpp"

class TmpTask: public rtos::task<> {
private:
    enum States { INITIAL_STATE, PLAY_STATE, DONE_STATE };
    States state = INITIAL_STATE;

    PlayerTask& plyerTask;
    rtos::clock clock;

public:
    TmpTask(PlayerTask& plyerTask): task(6, "tmpTask"), plyerTask(plyerTask), clock(this, 1'000'000, "clock") {};

    void main() override {
        while(true) {
            wait(clock);
            // Set time till start
            plyerTask.setMessage(0, 0, 4);
            wait(clock);
            // Set id to 1
            plyerTask.setMessage(0, 1, 0);
            plyerTask.setMessage(0, 1, 1);
            wait(clock);
            // Set damage to 2
            plyerTask.setMessage(0, 1, 1);
            plyerTask.setMessage(0, 1, 2);
            wait(clock);
            // Set life to 5
            plyerTask.setMessage(0, 1, 2);
            plyerTask.setMessage(0, 1, 5);
            wait(clock);
            // Start game
            plyerTask.setMessage(0, 0, 0);

            // Kill player
            for (uint8_t i = 0; i < 3; ++i) {
                wait(clock);
                hwlib::cout << "Preparing to fire!" << hwlib::endl;
                wait(clock);
                hwlib::cout << "3" << hwlib::endl;
                hwlib::cout << "2" << hwlib::endl;
                hwlib::cout << "1" << hwlib::endl;
                wait(clock);
                hwlib::cout << "Boooooom!" << hwlib::endl;
                plyerTask.setMessage(i + 1, 0, 2);
            }

            // This task is done
            while(true) wait(clock);
        }
    };
};

#endif // TMPTASK_HPP
