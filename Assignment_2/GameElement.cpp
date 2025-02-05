#include "GameElement.h"

//Default constructor
GameElement::GameElement() {
    interactMsg = "";
    gameToken = '\0';
}

//Destructor
GameElement::~GameElement() { 
    //cout << "GE destruc called" << endl; //For Testing
}

//Returns the game element's token
char GameElement::getToken() {
    return gameToken;
}

//Returns the interaction message
string GameElement::getMessage() {
    return interactMsg;
}

//Defines object/environment interaction with Mario.
void GameElement::interact(Mario *m) { }

//Defines enemy interaction with Mario.
bool GameElement::fight(Mario *m, RNG*& rng) {
    return true;
}
