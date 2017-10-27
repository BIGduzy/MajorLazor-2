#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "hwlib.hpp"

class PLAYER_HPP
{
private:
    int playerId, lives, power;
public:
    player():
    {}
    
    int getPlayerId() {
        return playerId;
    }
    
    int getLives() {
        return lives;
    }
    
    int getPower() {
        return power;
    }
    
    void setPlayerId( int value ) {
        playerId = value;
    }
    
    void setLives( int value ) {
        lives = value;
    }
    
    void setPower( int value ) {
        power = value;
    }
    
    void increaseLives( int amount = 1 ) {
        lives += amount;
    }
    
    void increasePower( int amount = 1 ) {
        power += amount;
    }
    
    int decreaseLives( int amount = 1 ) {
        if( (lives - amount) < 0 ){
            lives = 0;
        }
        else{
            lives -= amount;
        }
        return lives;
    }
    
    int decreasePower( int amount = 1 ) {
        if( (power - amount) < 0 ){
            power = 0;
        }
        else{
            power -= amount;
        }
        return power;
    }

};


#endif // PLAYER_HPP