#ifndef WARP_H
#define WARP_H

#include "GameElement.h"

//Dervied game element Warp Pipe
class Warp : public GameElement {
    public:
        Warp();
        ~Warp();

        void interact(Mario *m);
        
};

#endif