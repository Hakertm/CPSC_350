#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "ListQueue.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//Models a single customer for the student service center.
class Customer {
    public:
        Customer();
        Customer(string file_line, int arriveTime);
        ~Customer();

        //Getters
        int getVisitWaitTime();
        char getVisit();
        bool getStatus();
        int getTotalTime();
        int getWaitTime();
        int getArrivalTime();
        int getFinishTIme();
        bool getProgress();
        bool getQueueStatus();

        //Updaters
        void updateTotalWaitTime();
        void updateWaitTime(bool reset);
        void setProgress();
        void setQueueStatus();
        void setFinishTime(int time);
        void removeVisitItem();


    private:
        int finishTime;    //Time at which they will finish their business at an office.
        int arrivalTime;   //Time at which they arrive to the office.
        int totalWaitTime; //Used for stats later.
        int waitTime;      //Amount of time idling at a specific office. Reset when done at an office.
        bool finished;     //Whether or not the student is done with there business (all offices).
        bool inProgress;   //Whether or not a customer is in progress with their business.
        bool inQueue;
        
        ListQueue<int> *waitTimes;   //Wait times for each office they need to visit.
        ListQueue<char> *visitOrder; //Order in which they visit each office.

};

#endif