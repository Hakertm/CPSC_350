#ifndef GOOMBA_H
#define GOOMBA_H

#include "GameElement.h"

//Dervied game element Goomba
class Goomba : public GameElement {
    public:
        Goomba();
        ~Goomba();

        bool fight(Mario *m, RNG*& rng);
        
};

#endif