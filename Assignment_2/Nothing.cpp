#include "Nothing.h"

//Default constructor
Nothing::Nothing() {
    this->interactMsg = "The position is empty.";
    this->gameToken = 'x';
}

//Destructor
Nothing::~Nothing() {
    //cout << "Nothing destruc called." << endl; //For testing
}

//Defines object interaction with Mario
void Nothing::interact(Mario *m) { 
    //Literally nothing happens. What'd you expect?
}
