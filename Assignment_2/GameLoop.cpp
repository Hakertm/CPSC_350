#include "GameLoop.h"

//Default Constructor
GameLoop::GameLoop() {
    gameRng = new RNG();
    mario = new Mario(3);
    world = new World(gameRng);
    levelSize = world->getLevel(curLevel)->getLevelSize();
    curRow = gameRng->genNum(0, levelSize-1);
    curCol = gameRng->genNum(0, levelSize-1);
    numMoves = 0;
    curLevel = 0;
    finalBossAlive = true;
}

//Overloaded constructor
GameLoop::GameLoop(string input_file) {

    int cur_val;
    int index = 0;
    ifstream inS(input_file);

    if(inS.is_open()) {
        //Read input file values
        while(inS >> cur_val) {
            input_vals[index++] = cur_val;
        }
        inS.close();
    } else {
        throw runtime_error("Could not open input file. Does it exist?");
    }

    inS.close();


    gameRng = new RNG();

    //Assign objects with inputted values from file
    mario = new Mario(input_vals[2]);
    world = new World(input_vals[0], input_vals[1], input_vals[3], 
                      input_vals[4], input_vals[5], input_vals[6],
                      input_vals[7], gameRng);

    levelSize = input_vals[1];
    curRow = gameRng->genNum(0, levelSize-1);
    curCol = gameRng->genNum(0, levelSize-1);
    numMoves = 0;
    curLevel = 0;
    finalBossAlive = true;
}

//Destructor
GameLoop::~GameLoop() {
    delete gameRng;
    delete world;
    delete mario;

    //cout << "GameLoop destruc called" << endl; //For debugging/testing
}

//Core gameplay loop
void GameLoop::play(string output_file) {
    ofstream outS(output_file);

    if(outS.is_open()) {
        GameElement* gElement;
        char gToken;
        bool win;

        //Display world to output file
        outS << this->logGenWorld();

        //Game ends when either Mario has 0 lives or the final boss is defeated.
        while((mario->getLives() > 0) && (finalBossAlive)) {
            outS << this->logGenLevel();
            outS << this->logGenStats();

            //Used for triggering the right interaction
            gElement = world->getLevel(curLevel)->getElement(curRow, curCol);
            gToken = gElement->getToken();

            //Checks what game element Mario is on to trigger the right interaction.
            switch(gToken) {

                //Goomba and Koopa
                case 'g':
                case 'k':
                    //When at power level 0, Mario will keep fighting until he runs out of lives.
                    if(mario->getPwrLevel() == 0) {                      
                        while(mario->getLives() > 0) {                           
                            win = gElement->fight(mario, gameRng);
                            outS << gElement->getMessage() << "\n";
                            
                            //If Mario wins, the position is set to nothing.
                            if(win) {
                                world->getLevel(curLevel)->setElement(curRow, curCol, new Nothing()); //Set position to nothing
                                break;
                            }
                        }
                    } else {
                        win = gElement->fight(mario, gameRng);
                        outS << gElement->getMessage() << "\n"; 

                        //If Mario wins, the position is set to nothing.
                        if(win) {
                            world->getLevel(curLevel)->setElement(curRow, curCol, new Nothing()); //Set position to nothing
                        }
                    }

                    //Post stats and next move.
                    outS << this->logGenPostStats();
                    outS << this->logGenMove(this->move());

                    numMoves++;

                    break;

                //Level Boss
                case 'b':
                    //Constantly fights the boss until out of lives.
                    while(mario->getLives() > 0) {
                        //Final boss fight interaction (doesn't advance to a new level)
                        if(curLevel == world->getNumLevels() - 1) {
                            win = gElement->fight(mario, gameRng);
                            outS << gElement->getMessage() << "\n";

                            //If Mario wins, the position is set to nothing and changes the boss' status.
                            if(win) {
                                world->getLevel(curLevel)->setElement(curRow, curCol, new Nothing()); //Set position to nothing
                                finalBossAlive = false;
                                break;
                            }
                        //Standard boss interaction, advances to a new level.
                        } else {
                            win = gElement->fight(mario, gameRng);
                            outS << gElement->getMessage() << "\n";

                            //If Mario wins, the position is set to nothing and he advances to the next level.
                            if(win) {
                                world->getLevel(curLevel)->setElement(curRow, curCol, new Nothing()); //Set position to nothing
                                
                                //Goes to the next level at a new random position.
                                curLevel++;
                                curRow = gameRng->genNum(0, levelSize-1);
                                curCol = gameRng->genNum(0, levelSize-1);

                                break;
                            }
                        }
                    }

                    //Post stats and next move.
                    outS << this->logGenPostStats();
                    outS << this->logGenMove("advance to the next level");

                    numMoves++;
                    
                    break;

                //Warp Pipe
                case 'w':
                    outS << gElement->getMessage() << "\n";
                    outS << this->logGenPostStats();
                    outS << this->logGenMove("warp");

                    numMoves++;

                    //Goes to the next level at a new random position.
                    curLevel++;
                    curRow = gameRng->genNum(0, levelSize-1);
                    curCol = gameRng->genNum(0, levelSize-1);
                    
                    break;

                //Nothing, Mushroom, or Coin
                default:
                    gElement->interact(mario);
                    outS << gElement->getMessage() << "\n";
                    
                    world->getLevel(curLevel)->setElement(curRow, curCol, new Nothing()); //Set position to nothing
                    
                    //Post stats and next move.
                    outS << this->logGenPostStats();
                    outS << this->logGenMove(this->move());

                    numMoves++;

                    break;
            }

            //Checks which message to add to the log based on win/lose condition.
            if(mario->getLives() <= 0) {
                outS << "Game over! You lose.\n";
                outS << "Number of moves taken: " << numMoves << endl;
                
            } else if(!finalBossAlive) {
                outS << "Congrats! You saved the princess! You win!\n";
                outS << "Number of moves taken: " << numMoves << endl;
            }

            gElement = nullptr;
        }

        outS.close();

    } else {
        throw runtime_error("Could not open output file. Is it in use by another program?");
    }

    outS.close();
}

//Defines movement for mario in the game world, returning a string of his movement option. 
//5 movement options: Stay put or move up, down, left, or right.
string GameLoop::move() {
    int randNum = gameRng->genNum(1, 100);

    //5 possiblities, each with same probability of occuring (20%)
    if((randNum > 0) && (randNum <= 20)) { 
        //Stay Put
        return "stay put";

    } else if((randNum > 20) && (randNum <= 40)) {
        //Moves Up
        curRow--;

        //Checks if the row index is out of bounds to allow for wrapped movement on the grid.
        if(curRow < 0) {
            curRow = levelSize - 1;
            return "move up";
        } else {
            return "move up";
        }

    } else if ((randNum > 40) && (randNum <= 60)) {
        //Moves Down
        curRow++;

        //Checks if the row index is out of bounds to allow for wrapped movement on the grid.
        if(curRow > levelSize - 1) {
            curRow = 0;
            return "move down";
        } else {
            return "move down";
        }

    } else if ((randNum > 60) && (randNum <= 80)) {
        //Moves Left
        curCol--;
        
        //Checks if the column index is out of bounds to allow for wrapped movement on the grid.
        if(curCol < 0) {
            curCol = levelSize - 1;
            return "move left";
        } else {
            return "move left";
        }

    } else if ((randNum > 80) && (randNum <= 100)) {
        //Moves Right
        curCol++;

        //Checks if the column index is out of bounds to allow for wrapped movement on the grid.
        if(curCol > levelSize - 1) {
            curCol = 0;
            return "move right";
        } else {
            return "move right";
        }
    }
}

//Returns a text representation of the entire game world. Used for generating the output log file.
string GameLoop::logGenWorld() {
    string worldAsText;

    //Iterates through each level in the world and appends it to the string.
    for(int l = 0; l < world->getNumLevels(); ++l) {
        for(int r = 0; r < levelSize; ++r) {
            for(int c = 0; c < levelSize; ++c) {
                worldAsText += world->getLevel(l)->getElement(r, c)->getToken();
            }
            worldAsText += "\n";
        }
        worldAsText += "[-----------------------]\n";
    }

    worldAsText += "Mario is starting in position: (" + to_string(curRow) + "," + to_string(curCol) + ")\n";

    return worldAsText;
}

//Returns a text representation of the current level. Used for generating the output log file.
string GameLoop::logGenLevel() {
    string levelAsText;
    
    levelAsText += "[-----------------------]\n";

    //Appends each character of the level to the string and represents it as a 2D grid.
    for(int r = 0; r < levelSize; ++r) {
        for(int c = 0; c < levelSize; ++c) {
            if(r == curRow && c == curCol) {
                levelAsText += "H";
            } else {
                levelAsText += world->getLevel(curLevel)->getElement(r, c)->getToken();
            }
        }
        levelAsText += "\n";
    }

    levelAsText += "[-----------------------]\n";

    return levelAsText;
}

//Returns a string of the current level, and Mario's current position and power level.
//Used for generating the log output file.
string GameLoop::logGenStats() {
    string stats;

    stats += "Current Level: " + to_string(curLevel) + ". ";
    stats += "Mario is in position: (" + to_string(curRow) + "," + to_string(curCol) + "). ";
    stats += "Mario is at power level: " + to_string(mario->getPwrLevel()) + ".\n";

    return stats;
}

//Returns a string of some of Mario's stats after interacting.
string GameLoop::logGenPostStats() {
    string post;

    post += "Mario has " + to_string(mario->getLives()) + " lives left. ";
    post += "Mario has " + to_string(mario->getCoins()) + " coins.\n";

    return post;
}

//Returns a string of Mario's next move.
string GameLoop::logGenMove(string nextMove) {
    string future;
    
    future += "Mario will " + nextMove + ".\n";

    return future;
}
