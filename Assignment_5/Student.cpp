#include "Student.h"

//Default Constructor
Student::Student() {
    studID = 0;
    studName = "Name";
    studLevel = "Freshman"; //Class standing, e.g. Freshman, Sophomore, etc.
    studMajor = "Undeclared";
    studGPA = 0.0;
    advisorID = 0;
}

//Overloaded Constructor
Student::Student(int id, string name, string level, string major, double gpa, int advId) {    
    studID = id;
    studName = name;
    studLevel = level; //Class standing, e.g. Freshman, Sophomore, etc.
    studMajor = major;
    studGPA = gpa;
    advisorID = advId;
}

//Destructor
Student::~Student() {
    //cout << "Student Destructor Called." << endl; //For testing/debugging.
}

//Changes the student's advisor (based on ID).
void Student::changeAdvisor(int id) {
    advisorID = id;
}

//Prints the students information out to the terminal.
void Student::printStudInfo() {
    cout << "[----------------------]" << endl;
    cout << "Student ID: " << studID << endl;
    cout << "Name: " << studName << endl;
    cout << "Standing: " << studLevel << endl;
    cout << "Major: " << studMajor << endl;
    cout << "GPA: " << studGPA << endl;
    cout << "Advisor's ID: " << advisorID << endl;
    cout << "[----------------------]" << endl;
}


/****************************************\
|            Getter Functions            |
\****************************************/

//Returns the student's ID number.
int Student::getStudID() {
    return studID;
}

//Returns the student's advisor's ID number.
int Student::getAdvID() {
    return advisorID;
}


/****************************************\
|            Setter Function             |
\****************************************/

//Sets the student's advisor ID.
void Student::setAdvID(int id) {
    advisorID = id;
}


/****************************************\
|          Overloaded Operators          |
\****************************************/

//Equality. Compares student IDs.
bool operator==(const Student& leftStud, const Student& rightStud) {
    return leftStud.studID == rightStud.studID;
}

//Not equal. Compares student IDs.
bool operator!=(const Student& leftStud, const Student& rightStud) {
    return leftStud.studID != rightStud.studID;
}

//Less than. Compares student IDs.
bool operator<(const Student& leftStud, const Student& rightStud) {
    return leftStud.studID < rightStud.studID;
}

//Less than or equal to. Compares student IDs.
bool operator<=(const Student& leftStud, const Student& rightStud) {
    return leftStud.studID <= rightStud.studID;
}

//Greater than. Compares student IDs.
bool operator>(const Student& leftStud, const Student& rightStud) {
    return leftStud.studID > rightStud.studID;
}

//Greater than or equal to. Compares student IDs.
bool operator>=(const Student& leftStud, const Student& rightStud) {
    return leftStud.studID >= rightStud.studID;
}

//Insertion (<<).
ostream& operator<<(ostream& os, const Student& stud) {
    os << "[----------------------]" << endl;
    os << "Student ID: " << stud.studID << endl;
    os << "Name: " << stud.studName << endl;
    os << "Standing: " << stud.studLevel << endl;
    os << "Major: " << stud.studMajor << endl;
    os << "GPA: " << stud.studGPA << endl;
    os << "Advisor's ID: " << stud.advisorID << endl;
    os << "[----------------------]" << endl;
    return os;
}
