#ifndef SPEAKERVIEW_H
#define SPEAKERVIEW_H

#include "MonoStack.h"

#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

//Takes in a file of people's heights to determine who can see in each column.
class SpeakerView {
    public:
        SpeakerView();
        SpeakerView(string file_name);
        ~SpeakerView();

        void displayHeights();

    private:
        void processFile(string file);

        int numLines; //Number of Rows
        int numEntries; //Number of Columns
        GenStack<string> *myStack; //Used for holding file lines to be parsed later
        MonoStack<double>** heights; //Used for holding individual's heights

};

#endif