#include "ServiceCenter.h"

//Default Constructor
ServiceCenter::ServiceCenter() {
    offices = new Office*[3];
    waitTimeOverCount = 0;

    numStudents = 1;
    students = new Customer*[numStudents];
}

//Overloaded Constructor
ServiceCenter::ServiceCenter(string file_name) {
    offices = new Office*[3];
    numStudents = 0;
    waitTimeOverCount = 0;

    this->processFile(file_name); //Will update numStudents and students array.
}

//Destructor
ServiceCenter::~ServiceCenter() {
    for(int o = 0; o < 3; ++o) {
        delete offices[o];
    }

    delete[] offices;

    for(int s = 0; s < numStudents; ++s) {
        delete students[s];
    }

    delete[] students;
    
    //cout << "Service Center destruc called." << endl; //For debugging/testing.
}

//Runs a simulation of the student services center.
void ServiceCenter::simulate() {
    int tick = 1;

    //Ends when all students are finished at all offices.
    while(!(this->checkStudentStatus())) {

        //Iterate through each student
        for(int s = 0; s < numStudents; ++s) {
            Customer* stud = students[s];
            
            //Checks if they're completely done.
            if(stud->getStatus()) {
                //Do nothing with this student if they're done.
            
            //Check if they have arrived or not
            } else if(stud->getArrivalTime() <= tick) {
                
                //Students is not at an office AND not in a queue.
                if(!(stud->getProgress()) && !(stud->getQueueStatus())) {
                    this->findOffice(stud, tick);

                //Student is at an office.
                } else if(stud->getProgress()) {

                    //Check which office
                    switch(stud->getVisit()) {
                        case 'R':
                            if(offices[0]->checkIfFinished(stud, tick)) {
                                this->findOffice(stud, tick);
                            }
                            break;

                        case 'C':
                            if(offices[1]->checkIfFinished(stud, tick)) {
                                this->findOffice(stud, tick);
                            }
                            break;

                        case 'F':
                            if(offices[2]->checkIfFinished(stud, tick)) {
                                this->findOffice(stud, tick);
                            }
                            break;

                        default:
                            throw runtime_error("Invalid character.");
                            break;
                        
                    }
                }
            }
        
        }

        //Prevents stats from being incremented by one over.
        if(this->checkStudentStatus()) {
            break;
        }

        this->updateStats();
        ++tick;

    }
}

//Prints stats after a simulation ends.
void ServiceCenter::printStats() {
    for(int i = 0; i < 3; ++i) {
        offices[i]->calcStats();
        offices[i]->printWaitStats();
        offices[i]->printWindowStats();

        idleTimeOverCount += offices[i]->getIdleOverCount();
    }

    cout << endl;

    for(int s = 0; s < numStudents; ++s) {
        if(students[s]->getTotalTime() > 10) {
            ++waitTimeOverCount;
        }
    }

    cout << "Number of students waiting over 10 minutes across all offices: " << waitTimeOverCount << endl;
    cout << "Number of windows idle for over 5 minutes across all offices: " << idleTimeOverCount << endl;
}


//Checks whether or not all students are finished at each office
bool ServiceCenter::checkStudentStatus() {
    for(int i = 0; i < numStudents; ++i) {
        if(!(students[i]->getStatus())) {
            return false;
        }
    }

    return true;
}

//Process file, internal use.
void ServiceCenter::processFile(string file) {
    int index = 0;
    int fileLength = 0;
    string curr_line;
    ifstream inS(file);

    if(inS.is_open()) {
        //Count number of lines
        while(getline(inS, curr_line)) {
            ++fileLength;
        }

        if(fileLength < 6) {
            throw runtime_error("Invalid file length. Must have at least 6 lines");
        }

        inS.clear();
        inS.seekg(0, inS.beg);

        int index = 0;
        char offTypes[] = {'R', 'C', 'F'};
        string *file_contents = new string[fileLength];

        //Insert contents into array.
        while(getline(inS, curr_line)) {
            //First three lines of the file is always about number of windows per office.
            if(index < 3) {
                offices[index] = new Office(stoi(curr_line), offTypes[index]);
            }
            
            file_contents[index++] = curr_line;
        }

        index = 0;

        //Calculate the total number of students to arrive
        for(int i = 4; i < fileLength; i += stoi(file_contents[i]) + 2) {
            numStudents += stoi(file_contents[i]);
        }

        students = new Customer*[numStudents]; //Set length to number of students.

        //Populate students array with their data.
        //a for arrival time
        for(int a = 3; a < fileLength; a += stoi(file_contents[a+1]) + 2) {

            //s for student, their information
            for(int s = a + 2; s < (a + 2 + stoi(file_contents[a+1])); ++s) {
                students[index] = new Customer(file_contents[s], stoi(file_contents[a]));
                ++index;
            }
        }

        delete[] file_contents;

    } else {
        throw runtime_error("Could not open file.");
    }

    inS.close();
}

//Updates stats
void ServiceCenter::updateStats() {
    for(int i = 0; i < 3; ++i) {
        offices[i]->checkQueue();
        offices[i]->checkWindows();
    }
}

//Finds an office for the student to progress to.
void ServiceCenter::findOffice(Customer* c, int t) {
    //Prevents empty list being called.
    if(c->getStatus()) {
        return;
    }
    
    //Check which office is next.
    switch(c->getVisit()) {
        case 'R':
            offices[0]->findFreeWindow(c, t);
            break;

        case 'C':
            offices[1]->findFreeWindow(c, t);
            break;

        case 'F':
            offices[2]->findFreeWindow(c, t);
            break;

        default:
            throw runtime_error("Invalid character.");
            break;

    }
}
