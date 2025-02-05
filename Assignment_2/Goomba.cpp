#include "Goomba.h"

//Default constructor
Goomba::Goomba() {
    this->interactMsg = ""; //Determined during an interaction
    this->gameToken = 'g';
}

//Destructor
Goomba::~Goomba() {
    //cout << "Goomba destruc called." << endl; //For testing
}

//Defines object interaction with Mario
bool Goomba::fight(Mario *m, RNG*& rng) {
    int randN = rng->genNum(1, 100);
    
    //80% probability Mario can win
    if((randN >= 0) && (randN <= 80)) {
        m->updateNumWins(false);
        this->interactMsg = "Mario fought a Goomba and won.";
        return true;
    } else {
        m->updateNumWins(true);
        this->interactMsg = "Mario fought a Goomba and lost.";
        if(m->getPwrLevel() == 0) {
            m->updateLives(-1);
        } else {
            m->updatePwrLevel(-1);
        }
        return false;
    }
}
