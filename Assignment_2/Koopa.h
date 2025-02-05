#ifndef KOOPA_H
#define KOOPA_H

#include "GameElement.h"

//Dervied game element Koopa
class Koopa : public GameElement {
    public:
        Koopa();
        ~Koopa();

        bool fight(Mario *m, RNG*& rng);
        
};

#endif