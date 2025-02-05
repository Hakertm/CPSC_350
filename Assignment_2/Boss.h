#ifndef BOSS_H
#define BOSS_H

#include "GameElement.h"

//Dervied game element Boss
class Boss : public GameElement {
    public:
        Boss();
        ~Boss();
        
        bool fight(Mario *m, RNG*& rng);
        
};

#endif