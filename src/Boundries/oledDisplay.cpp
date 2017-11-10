#include <hwlib.hpp>

#include "oledDisplay.hpp"
#include "command.hpp"

void OledDisplay::layoutInitialstate() {
    for(int i = 0; i < 128; i++){
        display.write( hwlib::location( i, 0 ), hwlib::black );
    }
    for(int i = 0; i < 128; i++){
        display.write( hwlib::location( i, 63 ), hwlib::black );
    }
    for(int i = 0; i < 64; i++){
        display.write( hwlib::location( 0, i ), hwlib::black );
    }
    for(int i = 0; i < 64; i++){
        display.write( hwlib::location( 127, i ), hwlib::black );
    }
    displayOstream 
    << "\t0001" << "ID:"
    << "\t0002" << "Damage:"
    << "\t0003" << "Lives:"
    << "\t0004" << "StartTime:"
    << "\t0005" << "GameTime:"
    << hwlib::flush;
}

void OledDisplay::layoutPlaystate() {
    for(int i = 0; i < 128; i++){
        display.write( hwlib::location( i, 0 ), hwlib::black );
    }
    for(int i = 0; i < 128; i++){
        display.write( hwlib::location( i, 63 ), hwlib::black );
    }
    for(int i = 0; i < 64; i++){
        display.write( hwlib::location( 0, i ), hwlib::black );
    }
    for(int i = 0; i < 64; i++){
        display.write( hwlib::location( 127, i ), hwlib::black );
    }
    for(int i = 0; i < 128; i++){
        display.write( hwlib::location( i, 19 ), hwlib::black );
    }
    for(int i = 0; i < 128; i++){
        display.write( hwlib::location( i, 44), hwlib::black );
    }
    for(int i = 0; i < 18; i++){
        display.write( hwlib::location( 52, i), hwlib::black );
    }
     for(int i = 20; i < 44; i++){
        display.write( hwlib::location( 84, i), hwlib::black );
    }
    displayOstream 
    << "\t0101" <<"ID:" << "\t0701" << "Lives:"
    << "\t0103" << "Kills:--" << "\t1103" << "Time:"
    << "\t0104" << "Power:"
    << "\t0106" << "Streak:--"
    << hwlib::flush;
}

void OledDisplay::layoutDonestate() {
    for(int i = 0; i < 128; i++){
        display.write( hwlib::location( i, 0 ), hwlib::black );
    }
    for(int i = 0; i < 128; i++){
        display.write( hwlib::location( i, 63 ), hwlib::black );
    }
    for(int i = 0; i < 64; i++){
        display.write( hwlib::location( 0, i ), hwlib::black );
    }
    for(int i = 0; i < 64; i++){
        display.write( hwlib::location( 127, i ), hwlib::black );
    }
    displayOstream 
    << "\t0303" << "Gameover!"
    << hwlib::flush;
}

void OledDisplay::layoutLeaderstate() {
    for(int i = 0; i < 128; i++){
        display.write( hwlib::location( i, 0 ), hwlib::black );
    }
    for(int i = 0; i < 128; i++){
        display.write( hwlib::location( i, 63 ), hwlib::black );
    }
    for(int i = 0; i < 64; i++){
        display.write( hwlib::location( 0, i ), hwlib::black );
    }
    for(int i = 0; i < 64; i++){
        display.write( hwlib::location( 127, i ), hwlib::black );
    }
    displayOstream
    << "\t0101" << "Command:"
    << "\t0102" << "Value:"
    << hwlib::flush;
}

void OledDisplay::dataInitialstate(int id, int lives, int damage, int startTime, int gameTime) {
    displayOstream 
    << "\t0301" << id
    << "\t0702" << damage
    << "\t0603" << lives
    << "\t1004" << startTime
    << "\t0905" << gameTime
    << hwlib::flush;
}

void OledDisplay::dataPlaystate(int time, int playerId, int lives, int power) {
    displayOstream 
    << "\t0401" << playerId << "\t1301" << lives
    << "\t0704" << power << "\t1204" << time
    << hwlib::flush;
}

void OledDisplay::dataLeaderstate(bool validInput, int commandId, int value, bool send) {
    displayOstream
    << "\t0901" << commandId
    << "\t0902" << value
    << hwlib::flush;
    if(!validInput) {
        displayOstream << "\t0103" << "Invalid input" << hwlib::flush;
    }
    if(send) {
        displayOstream << "\t0104" << "Send" << hwlib::flush;
    }
}

void OledDisplay::clear(bool flush) {
    display.clear();
    if(flush){
        display.flush();
    }
}
