#include "Mario.h"

//Default Constructor
Mario::Mario() {
    nLives = 3;
    nCoins = 0;
    pwrLevel = 0;
    winCounter = 0;
}

//Overloaded Constructor
Mario::Mario(int lives) {
    if(lives > 0) {
        nLives = lives;
        nCoins = 0;
        pwrLevel = 0;
        winCounter = 0;
    } else {
        throw runtime_error("Input lives < or equal to 0. You want Mario dead already?");
    }
}

//Destructor
Mario::~Mario() {}

//Updates the number of coins by 1. Updates power level and resets the number of coins to zero if 
//20 coins are reached.
void Mario::updateCoins() {
    ++nCoins;
    // 20 coins grants 1 extra life and resets the coins to 0.
    if(nCoins == 20) {
        this->updateLives(1);
        nCoins = 0;
    }
}

//Updates the number of lives(decrease/increase)
void Mario::updateLives(int l) {
    nLives += l;
}

//Updates the power level(decrease/increase). Cannot go above 2 or below 0. Going below
void Mario::updatePwrLevel(int p) {
    pwrLevel += p;
    if(pwrLevel > 2) {
        pwrLevel = 2;
    } else if(pwrLevel < 0) {
        pwrLevel = 0;
        this->updateLives(-1);
    }
}

//Updates the number of wins Mario has had on his same life. Increases his number of lives by 1
//if he didn't lose a single battle on the same life 7 times in a row.
void Mario::updateNumWins(bool lose) {
    if(lose) {
        winCounter = 0;
    } else {
        ++winCounter;
        if(winCounter == 7) {
            this->updateLives(1);
            winCounter = 0;
        }
    }
}

//Returns the number of coins
int Mario::getCoins() {
    return nCoins;
}

//Returns the number of lives
int Mario::getLives() {
    return nLives;
}

//Returns the current power level
int Mario::getPwrLevel() {
    return pwrLevel;
}
