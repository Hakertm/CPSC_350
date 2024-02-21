#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "Model.h"

//Translates english words and sentences into Robber Language
class Translator 
{
    public:
        Translator(); 
        ~Translator();
        string translateEnglishWord(string word);
        string translateEnglishSentence(string sent);

    private:
        Model m; //Model object for method calls

};

#endif