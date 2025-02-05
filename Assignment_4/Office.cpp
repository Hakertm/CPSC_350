#include "Office.h"

//Default Constructor
Office::Office() {
    officeQueue = new ListQueue<Customer*>();
    officeType = 'R';
    
    meanIdleTime = 0;     //Windows
    longestIdleTime = 0;  //Windows
    numIdleOverCount = 0; //Windows
    meanWaitTime = 0;     //Customers
    longestWaitTime = 0;  //Customers

    numWindows = 3;
    custWaitTimes = new DLL<int>();
    windows = new Window* [numWindows];
}

//Overloaded constructor.
Office::Office(int nW, char type) {
    officeQueue = new ListQueue<Customer*>();
    officeType = type;

    meanIdleTime = 0.0;   //Windows
    longestIdleTime = 0;  //Windows
    numIdleOverCount = 0; //Windows
    meanWaitTime = 0;     //Customers
    longestWaitTime = 0;  //Customers

    numWindows = nW;
    custWaitTimes = new DLL<int>();
    windows = new Window* [numWindows];

    //Populates array with windows
    for(int i = 0; i < numWindows; ++i) {
        windows[i] = new Window();
    }
}

//Destructor
Office::~Office() {
    delete officeQueue;
    delete custWaitTimes;

    for(int i = 0; i < numWindows; ++i) {
        delete windows[i];
    }

    //cout << "Office destructor called." << endl;
}


/****************************************\
|             Core Functions             |
\****************************************/

//Finds the first available window and sets it to being in use, otherwise sends customer to queue.
void Office::findFreeWindow(Customer *cust, int currTime) {
    
    if(cust->getVisitWaitTime() == 0) {
        custWaitTimes->insertBack(cust->getWaitTime());
        cust->updateWaitTime(true);
        cust->removeVisitItem();
        return;
    }
    
    for(int w = 0; w < numWindows; ++w) {
        bool wStatus = windows[w]->getUseStatus();
        
        //If not in use, set as in use.
        if(!wStatus) {
            windows[w]->setUseStatus();
            cust->setFinishTime(currTime);
            cust->setProgress();
            return;
        }
    }

    cust->setQueueStatus();
    officeQueue->insert(cust);
}

//Checks if the queue is empty or not and updates stats accordingly.
void Office::checkQueue() {
    if(officeQueue->isEmpty()) {
        return;
    }

    int size = officeQueue->getSize();
    Customer** temp = new Customer*[size];

    //Updates stats
    for(int a = 0; a < size; ++a) {
        temp[a] = officeQueue->remove();
        temp[a]->updateWaitTime(false);
        temp[a]->updateTotalWaitTime();
    }

    //Reinserts into queue
    for(int b = 0; b < size; ++b) {
        officeQueue->insert(temp[b]);
    }

    delete[] temp; //Delete temp variable
}

//Checks which windows are idle to update their idle stats.
void Office::checkWindows() {
    for(int i = 0; i < numWindows; ++i) {
        //True when the window is not in use.
        if(!(windows[i]->getUseStatus())) {
            windows[i]->updateIdleTime();
        }
    }
}

//Checks if a customer is done with their business at the office.
//Also moves people from the queue to an open window.
bool Office::checkIfFinished(Customer *cust, int curTime) {
    if(cust->getFinishTIme() == curTime) {
        
        //Find first instance of a window in use and set it to not in use.
        for(int i = 0; i < numWindows; ++i) {
            //Checks if it's in use
            if(windows[i]->getUseStatus()) {
                windows[i]->setUseStatus();
                cust->setProgress();
                custWaitTimes->insertBack(cust->getWaitTime());
                cust->updateWaitTime(true);
                cust->removeVisitItem();
            }
        }

        //Move person in the queue to an available window (if not empty).
        if(!(officeQueue->isEmpty())) {
            officeQueue->peek()->setQueueStatus();
            this->findFreeWindow(officeQueue->remove(), curTime);
        }

        return true;
    }

    return false;
}


/****************************************\
|             Getter Function            |
\****************************************/

//Returns the number of windows that were idle for over 5 minutes.
int Office::getIdleOverCount() {
    return numIdleOverCount;
}


/****************************************\
|             Stats Functions            |
\****************************************/

//Calculates specific stats for window idle time and customer wait time.
void Office::calcStats() {
    double sum;
    
    /*
    * Calculating window idle stats
    */

    //Iterate through each window
    for(int i = 0; i < numWindows; ++i) {
        sum += double(windows[i]->getIdleTime());

        //Get longest idle time
        if(windows[i]->getIdleTime() > longestIdleTime) {
            longestIdleTime = windows[i]->getIdleTime();
        }

        if(windows[i]->getIdleTime() > 5) {
            ++numIdleOverCount;
        }
    }

    meanIdleTime = sum/double(numWindows);

    /*
    * Calculating customer idle stats
    */
    sum = 0.0;
    int numCust = custWaitTimes->getSize();

    //Iterate through each customer's wait time for this specific office
    for (int i = 0; i < numCust; ++i) {
        int val = custWaitTimes->removeBack();
        
        sum += double(val);

        //Get longest wait time
        if(val > longestWaitTime) {
            longestWaitTime = val;
        }
    }

    meanWaitTime = sum/(double)numCust;

}

//Prints the window stats for this specific office.
void Office::printWindowStats() {
    switch(officeType) {
        //Registrar
        case 'R':
            cout << "[------Registrar's Window Stats------]"<< endl;
            cout << "Mean Window Idle Time: " << meanIdleTime << endl;
            cout << "Longest Window Idle Time: " << longestIdleTime << endl;
            break;

        //Financial
        case 'F':
            cout << "[------Finanical Aid's Window Stats------]"<< endl;
            cout << "Mean Window Idle Time: " << meanIdleTime << endl;
            cout << "Longest Window Idle Time: " << longestIdleTime << endl;
            break;

        //Cashier
        case 'C':
            cout << "[------Cashier's Window Stats------]"<< endl;
            cout << "Mean Window Idle Time: " << meanIdleTime << endl;
            cout << "Longest Window Idle Time: " << longestIdleTime << endl;
            break;

        default:
            cout << "Uh oh, my stats aren't here?!?!" << endl; //For debugging/testing
            break;
    }

}

//Prints the customer stats for this specific office.
void Office::printWaitStats() {
    switch(officeType) {
        //Registrar
        case 'R':
            cout << "[------Registrar's Student Wait Stats------]"<< endl;
            cout << "Mean Student Wait Time: " << meanWaitTime << endl;
            cout << "Longest Student Wait Time: " << longestWaitTime << endl;
            break;

        //Financial
        case 'F':
            cout << "[------Finanical Aid's Student Wait Stats------]"<< endl;
            cout << "Mean Student Wait Time: " << meanWaitTime << endl;
            cout << "Longest Student Wait Time: " << longestWaitTime << endl;
            break;

        //Cashier
        case 'C':
            cout << "[------Cashier's Student Wait Stats------]"<< endl;
            cout << "Mean Student Wait Time: " << meanWaitTime << endl;
            cout << "Longest Student Wait Time: " << longestWaitTime << endl;
            break;
        
        default:
            cout << "Uh oh, my stats aren't here?!?!" << endl; //For debugging/testing
            break;
    }

}
