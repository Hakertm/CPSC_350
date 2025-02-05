#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include "RNG.h"
#include "Mario.h"

//Base abstract class for all game elements
class GameElement {
    public:
        GameElement();
        virtual ~GameElement();

        virtual void interact(Mario *m); //Used with objects/environment
        virtual bool fight(Mario* m, RNG*& rng); //Used with enemies
        virtual char getToken();
        virtual string getMessage();

    protected:
        string interactMsg;
        char gameToken;

};

#endif