#ifndef RNG_H
#define RNG_H

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

//Random number generator used in other classes
class RNG {
    public:
        RNG();
        ~RNG();

        int genNum(int lower, int upper);
};

#endif