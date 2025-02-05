#include "GameLoop.h"

int main(int argc, char **argv) {

    //Check if there is an arguement or not or the correct amount; prevents crash
    if(argc != 3) {
        cerr << "Invalid parameter count. Input format: ./a.out [input_file] [output_file]" << endl;
        return -4187598; //Social credit deduction
    }

    GameLoop *SuperMarioBros = new GameLoop(argv[1]);

    try {
        
        //Play one complete game of bootleg Super Mario Bros
        SuperMarioBros->play(argv[2]);

    } catch(runtime_error &excpt) {
        cout << excpt.what() << endl;
    }

    delete SuperMarioBros;

    return 0;
}
