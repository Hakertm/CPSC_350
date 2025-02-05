#ifndef LEVEL_H
#define LEVEL_H

#include "GameElement.h"
#include "Coin.h"
#include "Nothing.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Mushroom.h"
#include "Warp.h"
#include "Boss.h"

//Represents a single game level
class Level {
    public:
        Level(RNG*& l_rng);
        Level(int size, int pC, int pN, int pG, int pK, int pS, bool last, RNG*& l_rng);
        ~Level();

        GameElement* getElement(int row, int column);
        int getLevelSize();
        void setElement(int row, int column, GameElement* element);

        void printLevel(); //Debugging/Testing function

    private:
        //Parameters indicate percentage of level filled with certain objects/enemies.
        //The boolean parameter determines whether or not to place a warp pipe.
        void populateLevel(int pCoins, int pNothing, int pGoombas, 
                           int pKoopas, int pShrooms, bool lastLvl, RNG*& rng);
        GameElement*** gameLevel;
        int levelSize;
        int bossRow;
        int bossCol;
        
};

#endif