#include "FileProcessor.h"

int main() {

    FileProcessor *test = new FileProcessor();

    try {
        test->processFile("original.txt", "translation.html");
    } catch(runtime_error &excpt) {
        cerr << excpt.what() << endl;
    }

    delete test;
    return 0;
}
