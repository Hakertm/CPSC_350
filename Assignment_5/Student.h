#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>

using namespace std;

//Represents an individual student.
class Student{
    public:
        Student();
        Student(int id, string name, string level, string major, double gpa, int advId);
        ~Student();

        void changeAdvisor(int id);
        void printStudInfo(); 

        //Getters
        int getStudID();
        int getAdvID();

        //Setter
        void setAdvID(int id);

        //Overloaded Operators
        friend bool operator==(const Student& leftStud, const Student& rightStud);
        friend bool operator!=(const Student& leftStud, const Student& rightStud);
        friend bool operator<(const Student& leftStud, const Student& rightStud);
        friend bool operator<=(const Student& leftStud, const Student& rightStud);
        friend bool operator>(const Student& leftStud, const Student& rightStud);
        friend bool operator>=(const Student& leftStud, const Student& rightStud);
        friend ostream& operator<<(ostream& os, const Student& stud);

    private:
        int studID;
        string studName;
        string studLevel; //Class standing, e.g. Freshman, Sophomore, etc.
        string studMajor;
        double studGPA;
        int advisorID;
        
};

#endif