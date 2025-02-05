#ifndef WORLD_H
#define WORLD_H

#include "Level.h"

//Represents all the levels in the whole game world
class World {
    public:
        World(RNG*& w_rng);
        World(int levels, int lSize, int p_C, int p_N, int p_G, int p_K, int p_S, RNG*& w_rng);
        ~World();

        Level* getLevel(int levelNumber);
        int getNumLevels();

        void printWorld(); //Debugging/Testing function

    private:
        Level** gameWorld;
        int n_Levels;

};

#endif