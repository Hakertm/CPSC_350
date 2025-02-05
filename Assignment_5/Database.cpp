#include "Database.h"

//Default Constructor
Database::Database() {
    Students = new LazyBST<Student>();
    FacMembers = new LazyBST<Faculty>();
}

//Destructor
Database::~Database() {
    delete Students;
    delete FacMembers;

    //cout << "Database Destructor Called." << endl;
}

//Runs an instance of the database program.
void Database::startDB() {
    string num = "0";
    ofstream outS("runLog.txt");

    if(outS.is_open()) {
        //Ends when the user chooses the "Exit" command (11).
        while(stoi(num) != 11) {
            //Commands
            cout << "Type the corresponding number to the command you want to choose." << endl;
            cout << "(1)Print all students and their information by ascending ID number." << endl;
            cout << "(2)Print all faculty members and their information by ascending ID number." << endl;
            cout << "(3)Find and display a student's information given the student ID." << endl;
            cout << "(4)Find and display a faculty's information given the faculty ID." << endl;
            cout << "(5)Add a new student to the database." << endl;
            cout << "(6)Delete a student given the ID number." << endl;
            cout << "(7)Add a new faculty to the database." << endl;
            cout << "(8)Delete a faculty given the ID number." << endl;
            cout << "(9)Change a student's advisor given the student's ID and the new faculty ID." << endl;
            cout << "(10)Remove an advisee(s) from a faculty member given the IDs." << endl;
            cout << "(11)Exit." << endl;
            
            //User input
            cout << "Number: ";
            getline(cin, num);

            //Checks if the input is a number.
            while(!(isdigit(num[0]))) {
                cout << "Invalid input. Must be an integer number." << endl;
                
                cout << "Number: ";
                getline(cin, num);
            }

            cout << endl;

            //Checks which command to run.
            switch(stoi(num)) {
                case 1:
                    this->printStudents(outS);
                    break;

                case 2:
                    this->printFacMembers(outS);
                    break;

                case 3:
                    this->printStud();
                    break;

                case 4:
                    this->printFac();
                    break;

                case 5:
                    this->addStud();
                    break;

                case 6:
                    this->delStud();
                    break;

                case 7:
                    this->addFac();
                    break;

                case 8:
                    this->delFac();
                    break;

                case 9:
                    this->changeStudAdv();
                    break;

                case 10:
                    this->delAdvisees();
                    break;

                case 11:
                    break;

                default:
                    cout << "Invalid number." << endl << endl;
                    break;
            }
        }
    
    } else {
        throw runtime_error("Could not open file.");
    }

    cout << "Goodbye." << endl;

    outS.close();
}


/****************************************\
|            Command Functions           |
\****************************************/

//(1)Prints all students and their information in ascending ID number.
void Database::printStudents(ostream& output) {
    Students->printTree();
    Students->outputTree(output);
}

//(2)Prints all faculty members and their information in ascending ID number.
void Database::printFacMembers(ostream& output) {
    FacMembers->printTree();
    FacMembers->outputTree(output);
}

//(3)Finds and displays student information given the student ID.
void Database::printStud() {
    string id;

    cout << "Enter an ID: ";
    getline(cin, id);
    //cin >> id;

    //Check if the input value is an integer.
    if(integerCheck(id)) {
        cout << "Invalid input. Must be an integer." << endl << endl;
        return;
    }

    Student* stud = Students->search(Student(stoi(id), "", "", "", 0.0, 0));

    //Check if the student exists.
    if(stud == NULL) {
        cout << "Student does not exist." << endl << endl;
    } else {
        stud->printStudInfo();
    }

}

//(4)Finds and displays faculty information given the faculty ID.
void Database::printFac() {
    string id;

    cout << "Enter an ID: ";
    getline(cin, id);
    //cin >> id;

    //Check if the input value is an integer.
    if(integerCheck(id)) {
        cout << "Invalid input. Must be an integer." << endl << endl;
        return;
    }

    Faculty* fac = FacMembers->search(Faculty(stoi(id), "", "", ""));

    //Check if the student exists.
    if(fac == NULL) {
        cout << "Faculty does not exist." << endl << endl;
    } else {
        fac->printFacInfo();
    }

}

//(5)Add a new student to the database.
void Database::addStud() {
    string input[6]; 

    //ID
    cout << "Enter an ID: ";
    getline(cin, input[0]);
    //cin >> input[0];

    //Check if the input value is an integer.
    if(integerCheck(input[0])) {
        cout << "Invalid input. Must be an integer." << endl << endl;
        return;
    }

    //Name
    cout << "Enter a Name: ";
    getline(cin, input[1]);
    //cin >> input[1];

    //Standing
    cout << "Enter a Class Standing: ";
    getline(cin, input[2]);
    //cin >> input[2];

    //Major
    cout << "Enter a Major: ";
    getline(cin, input[3]);
    //cin >> input[3];

    //GPA
    cout << "Enter a GPA: ";
    getline(cin, input[4]);
    //cin >> input[4];

    //Custom version of integerCheck to check for doubles. Checks for the "." character.
    for(int i = 0; i < input[4].length(); ++i) {
        if(!(isdigit(input[4][i])) && !(input[4][i] == '.')) {
            cout << "Invalid input. Must be a decimal value." << endl << endl;
            return;
        }
    }

    //Advisor ID
    cout << "Enter an Advisor ID: ";
    getline(cin, input[5]);
    //cin >> input[5];
    cout << endl;

    //Check for valid ID or GPA.
    if(stoi(input[0]) <= 0 || stod(input[4]) < 0.0) {
        cout << "Invalid ID or GPA input. ID must be greater than 0, GPA must not be less than 0." << endl << endl;
        return;
    }

    Student stud(stoi(input[0]), input[1], input[2], input[3], stod(input[4]), stoi(input[5]));

    //Check if the ID is already taken.
    if(Students->contains(stud)) {
        cout << "Input ID already exists." << endl << endl;
        return;
    }

    //Check if the advisor exists.
    if(!(FacMembers->contains(Faculty(stoi(input[5]), "", "", "")))) {
        cout << "Input advisor ID does not exist." << endl << endl;
        return;
    }

    Students->insert(stud);

    //Add student to faculty member's advisee list.
    Faculty* fac = FacMembers->search(Faculty(stoi(input[5]), "", "", ""));
    fac->addAdvisee(stoi(input[0]));

}

//(6)Delete a student given the ID number.
void Database::delStud() {
    string id;

    cout << "Enter an ID: ";
    getline(cin, id);
    //cin >> id;

    //Check if the input value is an integer.
    if(integerCheck(id)) {
        cout << "Invalid input. Must be an integer." << endl << endl;
        return;
    }

    Student* stud = Students->search(Student(stoi(id), "", "", "", 0.0, 0));

    //Check if the student exists.
    if(stud == NULL) {
        cout << "Student does not exist." << endl << endl;
        return;
    }

    //Remove the Student from their advisor's advisee list.
    Faculty* fac = FacMembers->search(Faculty(stud->getAdvID(), "", "", ""));
    if(fac != NULL) {
        fac->removeAdvisee(stud->getStudID());
    }

    //Delete student.
    Students->deleteNode(Student(stoi(id), "", "", "", 0.0, 0));
    cout << "Successfully removed the student." << endl << endl;
    
}

//(7)Add a new faculty member to the database.
void Database::addFac() {
    string input[4];

    //ID
    cout << "Enter an ID: ";
    getline(cin, input[0]);
    //cin >> input[0];

    //Check if the input value is an integer.
    if(integerCheck(input[0])) {
        cout << "Invalid input. Must be an integer.";
        return;
    }

    //Name
    cout << "Enter a Name: ";
    getline(cin, input[1]);
    //cin >> input[1];

    //Role/Job
    cout << "Enter a Job or Role: ";
    getline(cin, input[2]);
    //cin >> input[2];

    //Department
    cout << "Enter a Department: ";
    getline(cin, input[3]);
    //cin >> input[3];
    cout << endl;

    //Check for valid ID.
    if(stoi(input[0]) <= 0) {
        cout << "Invalid ID. Must be greater than 0." << endl << endl;
        return;
    }

    Faculty fac(stoi(input[0]), input[1], input[2], input[3]);

    //Check if ID is already taken.
    if(FacMembers->contains(fac)) {
        cout << "Input ID already exists." << endl << endl;
        return;
    }

    FacMembers->insert(fac);

}

//(8)Delete a faculty member given the ID number.
void Database::delFac() {
    string id;

    cout << "Enter an ID: ";
    getline(cin, id);
    //cin >> id;

    //Check if the input value is an integer.
    if(integerCheck(id)) {
        cout << "Invalid input. Must be an integer." << endl << endl;
        return;
    }

    Faculty* fac = FacMembers->search(Faculty(stoi(id), "", "", ""));

    //Checks if the Faculty exists.
    if(fac == NULL) {
        cout << "Faculty does not exist." << endl << endl;
        return; 
    }

    //Check if removing the faculty member will compromise the database.
    if((Students->getNumNodes() > 0) && (FacMembers->getNumNodes() == 1)) {
        cout << "Due to no other faculty existing, cannot delete this faculty due to" << endl;
        cout << "other students not having a replacement advisor. Aborting command." << endl << endl;
        return;
    }

    //Remove Faculty
    FacMembers->deleteNode(Faculty(stoi(id), "", "", ""));
    cout << "Successfully removed the Faculty." << endl << endl;

    //Update student's advisors.
    DLL<int>* studIDs = fac->getAdvisees();
    Faculty* replacementFac = FacMembers->getRoot();

    //Iterate through each ID and switch the student's advisor.
    for(int i = 0; i < studIDs->getSize(); ++i) {
        int val = studIDs->removeBack();
        Student searchKey(val, "", "", "", 0.0, 0);

        //Add advisee to the faculty's list.
        replacementFac->addAdvisee(val);

        //Search for student and change their advisor.
        Students->search(searchKey)->changeAdvisor(replacementFac->getFacID());

    }
}

//(9)Change a student's advisor given the student's ID and the new faculty ID.
void Database::changeStudAdv() {
    string sID;
    string fID;

    cout << "Enter the Student's ID: ";
    getline(cin, sID);

    cout << "Enter the Faculty's ID: ";
    getline(cin, fID);
    
    //Check for valid input.
    if(integerCheck(fID) || integerCheck(sID)) {
        cout << "Invalid input. Must be an integer." << endl << endl;
        return;
    }

    //Search keys
    Student sKey(stoi(sID), "", "", "", 0.0, 0);
    Faculty fKey(stoi(fID), "", "", "");

    Student* stud = Students->search(sKey);
    Faculty* fac = FacMembers->search(fKey);

    //Checks if the Student or Faculty exists.
    if(stud == NULL) {
        cout << "Student does not exist." << endl << endl;
        return;
    } else if(fac == NULL) {
        cout << "Faculty does not exist." << endl << endl;
        return;
    }

    //Remove from old faculty advisee list
    Faculty* oldFac = FacMembers->search(Faculty(stud->getAdvID(), "", "", ""));
    oldFac->removeAdvisee(stoi(sID));

    //Change advisor and add to their advisee list.
    stud->changeAdvisor(stoi(fID));
    fac->addAdvisee(stoi(sID));

}

//(10)Remove an advisee(s) from a faculty member's advisee list given the IDs.
void Database::delAdvisees() {
    string fID;
    string sID; 

    //Ends when the user enters 0.
    while(true) {

        //Faculty to remove advisees from.
        cout << "Enter a faculty ID (type 0 to cancel/exit): " << endl;
        getline(cin, fID);

        //Check for integer value.
        while(integerCheck(fID)) {
            cout << "Invalid input. Must be an integer value." << endl;

            cout << "Enter a faculty ID (type 0 to cancel/exit): " << endl;
            getline(cin, fID);
        }

        Faculty* fac = FacMembers->search(Faculty(stoi(fID), "", "", ""));

        //Check if the faculty exists.
        if(fac == NULL) {
            cout << "Faculty does not exist." << endl << endl;
            return;
        }

        //Advisee to remove.
        cout << "Enter an advisee/student ID (type 0 to cancel/exit): ";
        getline(cin, sID);

        //Check for integer value.
        while(integerCheck(sID)) {
            cout << "Invalid input. Must be an integer value." << endl;

            cout << "Enter an advisee/student ID (type 0 to cancel/exit): " << endl;
            getline(cin, sID);
        }

        //Check if the student is in the advisee list.
        if(fac->getAdviseeID(stoi(sID)) == -1) {
            cout << "Student does not exist in the faculty's advisee list." << endl << endl;
            return;
        }

        Student* stud = Students->search(Student(stoi(sID), "", "", "", 0.0, 0));

        //Get substitute advisor.
        cout << "Note: Removing a student from an advisor's advisee list requires finding a" << endl;
        cout << "replacement or substitute advisor/faculty." << endl;
        cout << "Enter the ID of the substitute advisor: ";
        getline(cin, fID);

        //Check for integer value.
        while(integerCheck(fID)) {
            cout << "Invalid input. Must be an integer value." << endl;

            cout << "Enter the ID of the substiture advisor: " << endl;
            getline(cin, fID);
        }

        Faculty* repFac = FacMembers->search(Faculty(stoi(fID), "", "", ""));

        //Check if the substitute exists.
        while(repFac == NULL) {
            cout << "Replacement faculty does not exist. If no suitable replacement exists," << endl;
            cout << "then type the same ID of the Faculty you previously input." << endl;
            cout << "Enter the ID of the substitute advisor: ";
            getline(cin, fID);

            repFac = FacMembers->search(Faculty(stoi(fID), "", "", ""));
        }

        //Remove advisee and change the advisee's advisor.
        fac->removeAdvisee(stoi(sID));
        stud->changeAdvisor(stoi(fID));
        repFac->addAdvisee(stoi(sID));

    }
}

//Helper function for checking if strings are valid integers.
//Returns true if it isn't an integer, false other wise.
bool Database::integerCheck(string val) {
    //Iterate through each character.
    for(int i = 0; i < val.length(); ++i) {
        if(!(isdigit(val[i]))) {
            return true; //Not an integer
        }
    }

    return false;
}
