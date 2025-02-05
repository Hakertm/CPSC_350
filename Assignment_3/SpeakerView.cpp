#include "SpeakerView.h"

//Default constructor
SpeakerView::SpeakerView() {
    numLines = 1;
    numEntries = 1;
    myStack = new GenStack<string>();
    heights = new MonoStack<double>*[numEntries];
    heights[0] = new MonoStack<double>();
}

//Overloaded constructor
SpeakerView::SpeakerView(string file_name) {
    numLines = 0;
    numEntries = 0;
    myStack = new GenStack<string>(16);
    
    //Will update the parameters
    processFile(file_name);
}

//Destructor
SpeakerView::~SpeakerView() {

    //Delete each MonoStack
    for(int i = 0; i < numEntries; ++i) {
        delete heights[i];
    }

    delete[] heights;
    heights = nullptr;

    delete myStack;
    myStack = nullptr;

    //cout << "SpeakerView Destructor Called" << endl; //For testing

}

//Displays heights of all people who can see in each column.
void SpeakerView::displayHeights() {
    
    for(int col = 0; col < numEntries; ++col) {

        int nCanSee = heights[col]->getSize();

        cout << "In column " << col << " there are " << nCanSee << " people that can see. ";
        cout << "Their heights are: ";

        //Prints heights.
        for(int h = 0; h < nCanSee; ++h) {
            double personHeight = heights[col]->pop();

            //Prevent comma on the last value.
            if(h == nCanSee - 1) {
                cout << fixed << setprecision(2) << personHeight << " inches.";
            } else {
                cout << fixed << setprecision(2) << personHeight << ", ";
            }

        }

        cout << endl;
    }

}

//Utility function used in the overloaded constructor to process the file.
void SpeakerView::processFile(string file) {
    string curr_line;
    string curr_num;
    ifstream inS(file);

    //Check if file is open
    if(inS.is_open()) {
        
        //Read in each line of the file and update the number of lines.
        while(getline(inS, curr_line)) {
            myStack->push(curr_line);
            ++numLines; //Update variable
        }

        //Get number of entries per row.
        istringstream iSS(myStack->peek());

        while(getline(iSS, curr_num, ' ')) {
            ++numEntries;
        }

        iSS.clear(); //Reset string stream

        //Create array of empty monotonically decreasing stacks. Each MonoStack represents a column.
        heights = new MonoStack<double>*[numEntries];

        for(int i = 0; i < numEntries; ++i) {
            heights[i] = new MonoStack<double>(numLines, 'd');
        }

        //Fill each MonoStack with the heights of anyone who can see in each column.
        for(int line = 0; line < numLines; ++line) {
            iSS.str(myStack->pop());
            int index = 0;

            //Pushes values from each row to respective MonoStack.
            while(getline(iSS, curr_num, ' ')) {
                double val = stod(curr_num); //Casts string to double
                
                //Checks for negatives values (zero too).
                if(val > 0) {
                    heights[index++]->push(val);
                } else {
                    throw runtime_error("Input height less than or equal to zero.");
                }
            }

            iSS.clear(); //Reset string stream
        }

    } else {
        throw runtime_error("Could not open file.");
    }

    inS.close();
}
