#include "Mushroom.h"

//Default constructor
Mushroom::Mushroom() {
    this->interactMsg = "Mario ate a mushroom.";
    this->gameToken = 'm';
}

//Destructor
Mushroom::~Mushroom() {
    //cout << "Mushroom destruc called." << endl; //For testing
}

//Defines object interaction with Mario
void Mushroom::interact(Mario *m) {
    m->updatePwrLevel(1);
}
