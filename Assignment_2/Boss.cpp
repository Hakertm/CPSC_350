#include "Boss.h"

//Default constructor
Boss::Boss() {
    this->interactMsg = ""; //Determined during an interaction
    this->gameToken = 'b';
}

//Destructor
Boss::~Boss() {
    //cout << "Boss destruc called." << endl; //For testing
}

//Defines object interaction with Mario
bool Boss::fight(Mario *m, RNG*& rng) {
    int randN = rng->genNum(1, 100);
    
    //50% probability Mario can win
    if((randN > 0) && (randN <= 50)) {
        m->updateNumWins(false);
        this->interactMsg = "Mario fought the level boss and won.";
        return true;
    } else {
        m->updateNumWins(true);
        this->interactMsg = "Mario fought the level boss and lost.";
        if(m->getPwrLevel() == 0) {
            m->updateLives(-1);
        } else {
            m->updatePwrLevel(-2);
        }
        return false;
    }
}