#include "Faculty.h"

//Default Constructor
Faculty::Faculty() {
    facID = 0;
    facName = "Name";
    facLevel = "Unknown";
    facDepartment = "Unknown";
    advisees = new DLL<int>();
}

//Overloaded Constructor
Faculty::Faculty(int id, string name, string level, string department) {
    facID = id;
    facName = name;
    facLevel = level;
    facDepartment = department;
    advisees = new DLL<int>();
}

//Destructor
Faculty::~Faculty() {
    //delete advisees;
    
    //cout << "Faculty Destructor Called." << endl; //For debugging/testing.
}

//Removes one advisee from the faculty's list of advisees.
bool Faculty::removeAdvisee(int id) {
    //Checks if the ID is in the faculty's advisees list.
    if(advisees->find(id) == -1) {
        return false;
    }
    
    advisees->removeNode(id);
    return true; //Sucessfully removed.
}

//Adds an advisee to the faculty's list of advisees.
void Faculty::addAdvisee(int id) {
    advisees->insertBack(id);
}

//Print's the faculty member's information
void Faculty::printFacInfo() {
    cout << "[----------------------]" << endl;
    cout << "Faculty ID: " << facID << endl;
    cout << "Name: " << facName << endl;
    cout << "Job Title/Role: " << facLevel << endl;
    cout << "Department: " << facDepartment << endl;
    cout << "Advisee IDs: " << endl;
    cout << advisees->returnData();
    cout << "[----------------------]" << endl;
}


/****************************************\
|           Auxilary Function            |
\****************************************/

//Checks if the faculty member has no advisees.
bool Faculty::isEmpty() {
    return advisees->isEmpty();
}


/****************************************\
|            Getter Functions            |
\****************************************/

//Returns the faculty member's ID number.
int Faculty::getFacID() {
    return facID;
}

//Returns the advisee's ID number.
int Faculty::getAdviseeID(int id) {
    return advisees->find(id);
}

//Returns the list of advisee IDs.
DLL<int>* Faculty::getAdvisees() {
    return advisees;
}


/****************************************\
|          Overloaded Operators          |
\****************************************/

//Equality. Compares faculty IDs.
bool operator==(const Faculty& leftFac, const Faculty& rightFac) {
    return leftFac.facID == rightFac.facID;
}

//Not equal. Compares faculty IDs.
bool operator!=(const Faculty& leftFac, const Faculty& rightFac) {
    return leftFac.facID != rightFac.facID;
}

//Less than. Compares faculty IDs.
bool operator<(const Faculty& leftFac, const Faculty& rightFac) {
    return leftFac.facID < rightFac.facID;
}

//Less than or equal to. Compares faculty IDs.
bool operator<=(const Faculty& leftFac, const Faculty& rightFac) {
    return leftFac.facID <= rightFac.facID;
}

//Greater than. Compares faculty IDs.
bool operator>(const Faculty& leftFac, const Faculty& rightFac) {
    return leftFac.facID > rightFac.facID;
}

//Greater than or equal to. Compares faculty IDs.
bool operator>=(const Faculty& leftFac, const Faculty& rightFac) {
    return leftFac.facID >= rightFac.facID;
}

//Insertion (<<).
ostream& operator<<(ostream& os, const Faculty& fac) {
    os << "[----------------------]" << endl;
    os << "Faculty ID: " << fac.facID << endl;
    os << "Name: " << fac.facName << endl;
    os << "Job Title/Role: " << fac.facLevel << endl;
    os << "Department: " << fac.facDepartment << endl;
    os << "Advisee IDs: " << endl;
    os << fac.advisees->returnData();
    os << "[----------------------]" << endl;

    return os;
}
