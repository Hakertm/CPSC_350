#include "Translator.h"

//Default constructor
Translator::Translator() {}

//Default destructor
Translator::~Translator() {}

//Takes a string of an english word and returns it encoded in Robber Language
string Translator::translateEnglishWord(string word) {
    string rob_word = "";
    
    //Converts each letter to its respective Robber Language encoding
    for(int i = 0; i < word.length(); ++i) {
        rob_word += m.vowelChecker(word.at(i));
    }

    return rob_word;
}

//Takes a string of an english sentence and returns it encoded in Robber Language
string Translator::translateEnglishSentence(string sent) {
    string rob_sent = "";
    
    //Converts each letter to its respective Robber Language encoding
    for(int i = 0; i < sent.length(); ++i) {
        
        //Check for punctuation and white space
        if(ispunct(sent.at(i)) || isspace(sent.at(i))) {
            rob_sent += sent.at(i);
        } else {
            rob_sent += m.vowelChecker(sent.at(i));
        }
    }

    return rob_sent;
}
