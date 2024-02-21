#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "Translator.h"
#include <fstream>
#include <string>
#include <exception>

//Takes an input file of text and converts it into an HTML file showing the original
//and Robber Language version of the text.
class FileProcessor
{
    public:
        FileProcessor();
        ~FileProcessor();
        void processFile(string input, string output);

    private:
        //Translator object for method use
        Translator t;
};

#endif