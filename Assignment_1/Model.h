#ifndef MODEL_H
#define MODEL_H

#include <iostream>

using namespace std;

//Model class that encodes the rules for Robber Language
class Model
{
    public:
        Model();
        ~Model();
        string translateSingleConsonant(char c); 
        string translateSingleVowel(char v);
        string vowelChecker(char l); //Helper function
};

#endif