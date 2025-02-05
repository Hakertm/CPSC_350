#include "Koopa.h"

//Default constructor
Koopa::Koopa() {
    this->interactMsg = ""; //Determined during an interaction
    this->gameToken = 'k';
}

//Destructor
Koopa::~Koopa() {
    //cout << "Koopa destruc called." << endl; //For testing
}

//Defines object interaction with Mario
bool Koopa::fight(Mario *m, RNG*& rng) { 
    int randN = rng->genNum(1, 100);
    
    //65% probability Mario can win
    if((randN > 0) && (randN <= 65)) {
        m->updateNumWins(false);
        this->interactMsg = "Mario fought a Koopa and won.";
        return true;
    } else {
        m->updateNumWins(true);
        this->interactMsg = "Mario fought a Koopa and lost.";
        if(m->getPwrLevel() == 0) {
            m->updateLives(-1);
        } else {
            m->updatePwrLevel(-1);
        }
        return false;
    }
}
