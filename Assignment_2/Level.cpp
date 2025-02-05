#include "Level.h"

//"Default" constructor
Level::Level(RNG*& l_rng) {
    levelSize = 3;

    //Creates a levelSize x levelSize empty 2D GameElement pointer array
    gameLevel = new GameElement**[levelSize];
    for(int i = 0; i < levelSize; ++i) {
        gameLevel[i] = new GameElement*[levelSize];
    }

    //Populates level with certain percentages of each game element
    populateLevel(0, 0, 100, 0, 0, true, l_rng);
}

//Overloaded constructor, sets level size
Level::Level(int size, int pC, int pN, int pG, int pK, int pS, bool last, RNG*& l_rng) {
    if(size < 2) {
        throw runtime_error("Input level size < 2.");
    }
    
    levelSize = size;
    
    //Creates a levelSize x levelSize empty 2D GameElement pointer array
    gameLevel = new GameElement**[levelSize];
    for(int i = 0; i < levelSize; ++i) {
        gameLevel[i] = new GameElement*[levelSize];
    }

    //Populates level with certain percentages of each game element
    populateLevel(pC, pN, pG, pK, pS, last, l_rng);
}

//Destructor
Level::~Level() {
    //Delete GameElement arrays and GameElements
    for(int iRow = 0; iRow < levelSize; ++iRow) {
        for(int iColumn = 0; iColumn < levelSize; ++iColumn) {
            delete gameLevel[iRow][iColumn];
        }
        delete[] gameLevel[iRow];
    }

    delete[] gameLevel; //Delete array of pointers to pointers to GameElements pointers array
    gameLevel = nullptr;
    
    //cout << "Level destruc called." << endl; //For debugging/testing
}

//Populates the level with a certain percentage of coins, nothing, goombas, koopas, or mushrooms. 
//Mininum of one boss and warp pipe each level. However, no warp pipe on the last level.
void Level::populateLevel(int pCoins, int pNothing, int pGoombas, 
                          int pKoopas, int pShrooms, bool lastLvl, RNG*& rng) 
{
    int randRowWarp = rng->genNum(0, levelSize-1); //For use with placing warp pipe
    int randColWarp = rng->genNum(0, levelSize-1);
    int randRowBoss = rng->genNum(0, levelSize-1); //For use with placing a boss
    int randColBoss = rng->genNum(0, levelSize-1);
    int randNum; //For placing object/enemy
    int lower;
    int upper;
    
    //Checks if the input percentages are equal to 100
    if((pCoins + pNothing + pGoombas + pKoopas + pShrooms) == 100) { 

        //Populates each cell with a randomly chosen object/enemy.
        for(int row = 0; row < levelSize; ++row) {
            for(int column = 0; column < levelSize; ++column) {
                randNum = rng->genNum(1, 100);
                //cout << randNum << endl; //For Debugging/Testing
                lower = 0;
                upper = pCoins;

                //Coin
                if((randNum > lower) && (randNum <= upper)) {
                    gameLevel[row][column] = new Coin();
                }
                lower = pCoins; //Update upper+lower bounds
                upper = pCoins + pNothing;

                //Nothing
                if((randNum > lower) && (randNum <= upper)) {
                    gameLevel[row][column] = new Nothing();
                }
                lower = upper;
                upper += pGoombas;

                //Goomba
                if((randNum > lower) && (randNum <= upper)) {
                    gameLevel[row][column] = new Goomba();
                }
                lower = upper;
                upper += pKoopas;

                //Koopa
                if((randNum > lower) && (randNum <= upper)) {
                    gameLevel[row][column] = new Koopa();
                }
                lower = upper;
                upper += pShrooms;
                
                //Shroom
                if((randNum > lower) && (randNum <= upper)) {
                    gameLevel[row][column] = new Mushroom();
                }
            }
        }

        //Checks if it's the last level to determine whether or not to place a warp pipe.
        if(lastLvl) {
            this->setElement(randRowBoss, randColBoss, new Boss());

        } else {
            this->setElement(randRowWarp, randColWarp, new Warp());

            //Prevent boss location being set to same as the warp pipe.
            do {
                randRowBoss = rng->genNum(0, levelSize-1);
                randColBoss = rng->genNum(0, levelSize-1);

                this->setElement(randRowBoss, randColBoss, new Boss());
            }
            while((randRowBoss == randRowWarp) && (randColBoss == randColWarp));
        }

    } else {
        throw runtime_error("Combined percentages from input file are > 100 or < 100.");
    }
}

//Returns the element at index row, column.
GameElement* Level::getElement(int row, int column) {
    return gameLevel[row][column];
}

//Returns the level's size
int Level::getLevelSize() {
    return levelSize;
}

//Changes/Sets the element at index row, column.
void Level::setElement(int row, int column, GameElement* element) {
    delete gameLevel[row][column];
    gameLevel[row][column] = element;
}

//Debugging/Testing function. Prints the level to the console.
void Level::printLevel(){
    for(int row = 0; row < levelSize; ++row) {
        for(int column = 0; column < levelSize; ++column) {
            cout << gameLevel[row][column]->getToken();
        }
        cout << endl;
    }
}
