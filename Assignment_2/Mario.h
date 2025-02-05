#ifndef MARIO_H
#define MARIO_H

#include <iostream>

using namespace std;

//Contains the various stats and update methods of our hero.
class Mario {
    public:
        Mario();
        Mario(int lives);
        ~Mario();

        //Updaters/Setters
        void updateCoins();
        //Both functions below use a parameter to avoid the need of making an additional
        //function for decrementing both of these stats.
        void updateLives(int l);
        void updatePwrLevel(int p);
        void updateNumWins(bool lose);

        //Getters
        int getCoins();
        int getLives();
        int getPwrLevel();

    private:
        //Character Stats
        int nLives;
        int nCoins;
        int pwrLevel;
        int winCounter;

};

#endif