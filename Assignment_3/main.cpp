#include "SpeakerView.h"

int main(int argc, char **argv) {

    //Check if there is an arguement or not, or the correct amount of arguements; prevents crash.
    if(argc != 2) {
        cerr << "Invalid parameter count. Input format: ./a.out [input_file]" << endl;
        return -4187598; //Social credit deduction
    }

    //Create SpeakerView object with input file from the command line.
    SpeakerView *mySV = new SpeakerView(argv[1]);

    try {

        //Display the heights to the console.
        mySV->displayHeights();

    } catch(runtime_error &excpt) {
        cout << excpt.what() << endl;
    }

    delete mySV;

}