#include "Database.h"

int main(int argc, char **argv) {

    //Check if there is an arguement or not, or the correct amount of arguements; prevents crash.
    if(argc != 1) {
        cerr << "Invalid parameter count. Input format: ./a.out" << endl;
        return -4187598; //Social credit deduction
    }

    Database* DB = new Database();

    try {

        DB->startDB();

    } catch(runtime_error &excpt) {
        cout << excpt.what() << endl;
    }

    delete DB;

}