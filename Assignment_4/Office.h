#ifndef OFFICE_H
#define OFFICE_H

#include "Window.h"
#include "Customer.h"

//Models a single office at the student service center.
class Office {
    public:
        Office();
        Office(int nW, char type);
        ~Office();

        //Finds the first available window
        void findFreeWindow(Customer *cust, int currTime);
        
        //Checks if one these is empty to update idle time stats.
        void checkQueue();
        void checkWindows();
        
        //Returns whether or not if a customer is done.
        bool checkIfFinished(Customer *cust, int curTime);
        
        //Getter
        int getIdleOverCount();

        //Stats
        void calcStats();
        void printWindowStats();
        void printWaitStats();

    private:
        ListQueue<Customer*> *officeQueue;

        char officeType; //Designates if the office is Registrar, Financial Aid, or Cashier

        double meanIdleTime;     //Windows
        int longestIdleTime;  //Windows
        int numIdleOverCount; //Windows
        double meanWaitTime;     //Customers
        int longestWaitTime;  //Customers
        
        DLL<int> *custWaitTimes; //Linked list of the total wait times for each customer.
                                 //For stat calculation.

        int numWindows;
        Window **windows;        //Will be an array of windows.
        
};

#endif