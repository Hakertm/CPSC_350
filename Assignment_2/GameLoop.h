#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "World.h"
#include <fstream>
#include <string>

using namespace std;

//Defines the general gameplay loop and instantiates an instance of a functional game world
class GameLoop {
    public:
        GameLoop();
        GameLoop(string input_file);
        ~GameLoop();

        void play(string output_file);

    private:
        string move(); //Defines movement for mario in the world
        
        //Log generation
        string logGenWorld();
        string logGenLevel();
        string logGenStats();
        string logGenPostStats();
        string logGenMove(string move);

        RNG* gameRng;
        Mario* mario;
        World* world;
        int curRow;
        int curCol;
        int curLevel;
        int numMoves;
        int levelSize;
        bool finalBossAlive;
        int input_vals[8];

};

#endif