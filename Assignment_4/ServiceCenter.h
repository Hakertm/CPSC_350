#ifndef SERVICE_CENTER_H
#define SERVICE_CENTER_H

#include "Office.h"

//#include <typeinfo> //For debugging
#include <fstream>
#include <sstream>

//Models the service center
class ServiceCenter {
    public:
        ServiceCenter();
        ServiceCenter(string file_name);
        ~ServiceCenter();

        //Checks if all students are finished.
        bool checkStudentStatus();

        //Runs a simulation of the student services center.
        void simulate();

        //Print stats
        void printStats();

    private:
        //Helper functions for internal use.
        void processFile(string file);
        void updateStats();
        void findOffice(Customer* c, int t);

        int numStudents;
        int waitTimeOverCount;
        int idleTimeOverCount;

        Office** offices;
        Customer** students;
        
};

#endif