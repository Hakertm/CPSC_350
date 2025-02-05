#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "GameElement.h"

//Dervied game element Mushroom
class Mushroom : public GameElement {
    public:
        Mushroom();
        ~Mushroom();

        void interact(Mario *m);
        
};

#endif