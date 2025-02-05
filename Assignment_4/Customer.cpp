#include "Customer.h"

//Default constructor
Customer::Customer() {
    finishTime = 0;
    arrivalTime = 0;
    totalWaitTime = 0;
    waitTime = 0;
    finished = false;
    inProgress = false;
    inQueue = false;

    waitTimes = new ListQueue<int>();
    visitOrder = new ListQueue<char>();
}

//Overloaded constructor
Customer::Customer(string file_line, int arriveTime) {
    finishTime = 0;
    arrivalTime = arriveTime;
    totalWaitTime = 0;
    waitTime = 0;
    finished = false;
    inProgress = false;
    inQueue = false;

    waitTimes = new ListQueue<int>();
    visitOrder = new ListQueue<char>();

    //For populating waitTimes and visitOrder
    int i = 0;
    string val;
    istringstream iSS(file_line);

    //Parse string to assign each value to its respective queue.
    while(getline(iSS, val, ' ')) {
        if(i < 3) {
            waitTimes->insert(stoi(val)); //Cast to int
        } else {
            visitOrder->insert(val[0]);
        }
        
        ++i;
    }
}

//Destructor
Customer::~Customer() {
    delete waitTimes;
    delete visitOrder;

    //cout << "Customer destuctor called." << endl; //For debugging/testing
}


/****************************************\
|           Getter Functions             |
\****************************************/

//Returns the wait time.
int Customer::getVisitWaitTime() {
    return waitTimes->peek();
}

//Returns the char value indicating which office the customer will visit.
char Customer::getVisit() {
    return visitOrder->peek();
}

//Gets the status of whether or not a student is done with their business.
bool Customer::getStatus() {
    //If both the queues are empty, that means the customer has finished all of their business
    //at the student services center.
    if(waitTimes->isEmpty() && visitOrder->isEmpty()) {
        return !finished;
    }
    
    return finished;
}

//Returns the customer's total wait time.
int Customer::getTotalTime() {
    return totalWaitTime;
}

//Returns the wait time at a specific office.
int Customer::getWaitTime() {
    return waitTime;
}

//Returns the arrival time
int Customer::getArrivalTime() {
    return arrivalTime;
}

//Returns the time the student will finish their business at the specific office.
int Customer::getFinishTIme() {
    return finishTime;
}

//Returns the inProgress variable
bool Customer::getProgress() {
    return inProgress;
}

//Returns the inQueue variable
bool Customer::getQueueStatus() {
    return inQueue;
}

/****************************************\
|           Updater Functions            |
\****************************************/

//Updates the total wait time by one.
void Customer::updateTotalWaitTime() {
    ++totalWaitTime;
}

//Updates the office wait time by one. Can reset to zero based on parameter option.
void Customer::updateWaitTime(bool reset = false) {
    if(reset) {
        waitTime = 0;
        return;
    }
    
    ++waitTime;
}

//Changes the inQueue status
void Customer::setQueueStatus() {
    inQueue = !inQueue;
}

//Changes the inProgress status
void Customer::setProgress() {
    inProgress = !inProgress;
}

//Sets the finish time
void Customer::setFinishTime(int time) {
    finishTime = waitTimes->peek() + time;
}

//Removes an item from the queue.
void Customer::removeVisitItem() {
    visitOrder->remove();
    waitTimes->remove();
}
