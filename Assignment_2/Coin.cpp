#include "Coin.h"

//Default constructor
Coin::Coin() {
    this->interactMsg = "Mario collected a coin.";
    this->gameToken = 'c';
}

//Destructor
Coin::~Coin() {
    //cout << "Coin destruc called." << endl; //For testing
}

//Defines object interaction with Mario
void Coin::interact(Mario *m) {
    m->updateCoins();
}
