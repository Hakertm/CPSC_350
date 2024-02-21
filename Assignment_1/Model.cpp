#include "Model.h"

//Default constructor
Model::Model() {}

//Default destructor
Model::~Model() {}

//Takes a consonant character and returns a string encoded in Robber Language
//Formula: consonant + 'o' + consonant
string Model::translateSingleConsonant(char c) {
    string rob = "";
    
    //Checks if upper case so second consonant isn't uppercase as well
    if(isupper(c)) {
        char lower_c = tolower(c);
        return rob + c + "o" + lower_c;
    }
    return rob + c + "o" + c;
}

//Takes a vowel character and returns a string of itself
string Model::translateSingleVowel(char v) {
    string vowel = "";
    return vowel + v;
}

//Checks if the character is a vowel or not and applies the correct conversion
string Model::vowelChecker(char l) {
    switch (l) {
        //Vowels
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return translateSingleVowel(l);
        //Consonants
        default:
            return translateSingleConsonant(l);
    }
}
