#include "Warp.h"

//Default constructor
Warp::Warp() {
    this->interactMsg = "Mario found a warp pipe.";
    this->gameToken = 'w';
}

//Destructor
Warp::~Warp() {
    //cout << "Warp destruc called." << endl; //For testing
}

//Defines object interaction with Mario
void Warp::interact(Mario *m) { 
    //Doesn't update his stats, so nothing happens to him.
}
