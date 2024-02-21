#include "FileProcessor.h"

//Default constructor
FileProcessor::FileProcessor() {}

//Default destructor
FileProcessor::~FileProcessor() {}

//Takes an input file containing text outputs it to or creates an HTML file
//containing the original text and the Robber Language version of it.
void FileProcessor::processFile(string input, string output) {
    string curr_line;
    ifstream inS(input);
    ofstream outS(output);

    //TODO: Add HTML Formatting
    if(inS.is_open() || outS.is_open()) {
        //Beginning HTML formatting
        outS << "<!DOCTYPE html>" << endl;
        outS << "<html>" << endl;
        outS << "<head>" << endl;
        outS << "<title>English to Robber Translation</title>" << endl;
        outS << "</head>" << endl;
        outS << "<body>" << endl;
        
        //Output text to file in normal format
        while(getline(inS, curr_line)) {
            outS << "<p><b>" << curr_line << "</b><br></p>";
        }

        //For adding the extra space in the middle (\n alone doesn't work when viewing through browser)
        outS << "<p><b></b><br></p>" << "\n";

        //Reset input stream
        inS.clear();
        inS.seekg(0, inS.beg);

        //Output text to file in Robber Language Format
        while(getline(inS, curr_line)) {
            outS << "<p><i>" << t.translateEnglishSentence(curr_line) << "</i><br></p>";
        }

        //Final HTML formatting
        outS << "\n<body>" << endl;
        outS << "</html>" << endl;
    
    } else {
        throw runtime_error("Could not open file.");
    }

    inS.close();
    outS.close();
}
