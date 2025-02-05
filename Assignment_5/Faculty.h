#ifndef FACULTY_H
#define FACULTY_H

#include "DBlList.h"

#include <iostream>
#include <string>

using namespace std;

//Represents an individual faculty member.
class Faculty{
    public:
        Faculty();
        Faculty(int id, string name, string level, string department);
        ~Faculty();

        bool removeAdvisee(int id);
        void addAdvisee(int id);
        void printFacInfo();

        //Auxilary Function
        bool isEmpty();

        //Getters
        int getFacID();
        int getAdviseeID(int id);
        DLL<int>* getAdvisees();

        //Overloaded Operators
        friend bool operator==(const Faculty& leftFac, const Faculty& rightFac);
        friend bool operator!=(const Faculty& leftFac, const Faculty& rightFac);
        friend bool operator<(const Faculty& leftFac, const Faculty& rightFac);
        friend bool operator<=(const Faculty& leftFac, const Faculty& rightFac);
        friend bool operator>(const Faculty& leftFac, const Faculty& rightFac);
        friend bool operator>=(const Faculty& leftFac, const Faculty& rightFac);
        friend ostream& operator<<(ostream& os, const Faculty& fac);

    private:
        int facID;
        string facName;
        string facLevel; //Role or Job Title, e.g. Lecturer, Assistant Prof, etc.
        string facDepartment;
        DLL<int> *advisees;

};

#endif