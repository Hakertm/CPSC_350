#include "World.h"

//"Default" Constructor
World::World(RNG*& w_rng) {
    n_Levels = 1;
    gameWorld = new Level*[n_Levels];

    for(int level = 0; level < n_Levels; ++level) {
        gameWorld[level] = new Level(w_rng);
    }
}

//Overloaded Constructor
World::World(int levels, int lSize, int p_C, int p_N, int p_G, int p_K, int p_S, RNG*& w_rng) {
    if(levels < 1) {
        throw runtime_error("Input number of levels less than 1.");
    }

    n_Levels = levels;
    gameWorld = new Level*[n_Levels];

    for(int level = 0; level < n_Levels; ++level) {
        //Checks if it's the last level.
        if(level == n_Levels-1) {
            gameWorld[level] = new Level(lSize, p_C, p_N, p_G, p_K, p_S, true, w_rng);
        } else {
            gameWorld[level] = new Level(lSize, p_C, p_N, p_G, p_K, p_S, false, w_rng);
        }
    }
}

//Destructor
World::~World() {
    for(int level = 0; level < n_Levels; ++level) {
        delete gameWorld[level];
    }
    
    delete[] gameWorld;
    gameWorld = nullptr;

    //cout << "World destruc called." << endl; //For debugging/testing.
}

//Returns the specified level from the world.
Level* World::getLevel(int levelNumber) {
    return gameWorld[levelNumber];
}

//Returns the number of levels in the world.
int World::getNumLevels() {
    return n_Levels;
}

//Prints the levels of the world to the console. For Debugging/Testing.
void World::printWorld() {
    for(int level = 0; level < n_Levels; ++level) {
        gameWorld[level]->printLevel();
        cout << endl;
    }
}
