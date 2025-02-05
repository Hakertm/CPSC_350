#include "ServiceCenter.h"

int main(int argc, char **argv) {

    //Check if there is an arguement or not, or the correct amount of arguements; prevents crash.
    if(argc != 2) {
        cerr << "Invalid parameter count. Input format: ./a.out [input_file]" << endl;
        return -4187598; //Social credit deduction
    }


    ServiceCenter *scc = new ServiceCenter(argv[1]);


    try {

        scc->simulate();
        scc->printStats();

    } catch(runtime_error &excpt) {
        cout << excpt.what() << endl;
    }

    delete scc;

}