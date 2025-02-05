#include "Window.h"

//Default constructor
Window::Window() {
    inUse = false;
    idleTime = 0;
}

//Destructor
Window::~Window() {
    //cout << "Window destructor called." << endl; //For testing/debugging
}


/****************************************\
|            Getter Functions            |
\****************************************/

//Returns the status of whether or not the window is in use.
bool Window::getUseStatus() {
    return inUse;
}

//Returns the total idle wait time
int Window::getIdleTime() {
    return idleTime;
}


/****************************************\
|        Setter/Updater Functions        |
\****************************************/

//Switchs the status of in use.
void Window::setUseStatus() {
    inUse = !inUse;
}

//Updates the idle time by one.
void Window::updateIdleTime() {
    ++idleTime;
}
