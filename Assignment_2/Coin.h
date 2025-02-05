#ifndef COIN_H
#define COIN_H

#include "GameElement.h"

//Dervied game element Coin
class Coin : public GameElement {
    public:
        Coin();
        ~Coin();

        void interact(Mario *m);
        
};

#endif