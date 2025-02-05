#ifndef NOTHING_H
#define NOTHING_H

#include "GameElement.h"

//Dervied game element Nothing
class Nothing : public GameElement {
    public:
        Nothing();
        ~Nothing();

        void interact(Mario *m);
        
};

#endif