#include "RNG.h"

//Default constructor
RNG::RNG() {
    srand(time(NULL));
}

//Destructor
RNG::~RNG() {
    //cout << "RNG destruc called" << endl; //For debugging/testing
}

//Generates a random number based on the upper and lower bound(both inclusive)
int RNG::genNum(int lower, int upper) {
    return (rand() % upper - lower + 1) + lower;
}
