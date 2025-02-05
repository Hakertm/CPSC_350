#ifndef DATABASE_H
#define DATABASE_H

#include "LazyBST.h"
#include "Student.h"
#include "Faculty.h"

//Database class containing an LBST of Students and Faculty Members with various commands available.
class Database{
    public:
        Database();
        ~Database();

        //Starts the Database
        void startDB();

    private:
        //Commands
        void printStudents(ostream& output);
        void printFacMembers(ostream& output);
        void printStud();
        void printFac();
        void addStud();
        void delStud();
        void addFac();
        void delFac();
        void changeStudAdv();
        void delAdvisees();

        //Helper function.
        bool integerCheck(string val);

        LazyBST<Student>* Students;
        LazyBST<Faculty>* FacMembers;

};

#endif