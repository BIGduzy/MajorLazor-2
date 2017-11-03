#ifndef SPEAKER_HPP
#define SPEAKER_HPP

#include "hwlib.hpp"

namespace target = hwlib::target;

class Speaker {
private:
    hwlib::pin_out& lsp;
public:
    Speaker(hwlib::pin_out& lsp):
        lsp(lsp)
    {};

    void startSpeaker() {
        lsp.set(1);
    }

    void stopSpeaker() {
        lsp.set(0);
    }
};

#endif // SPEAKER_HPP
