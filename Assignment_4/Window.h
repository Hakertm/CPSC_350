#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

using namespace std;

//Models a single window at an office.
class Window {
    public:
        Window();
        ~Window();

        //Getters
        bool getUseStatus();
        int getIdleTime();

        //Setters/Updaters
        void setUseStatus();
        void updateIdleTime();

    private:
        bool inUse;
        int idleTime;
        
};

#endif