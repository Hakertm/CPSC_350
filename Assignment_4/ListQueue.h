#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include "DBlList.h"

using namespace std;

//List-Based Template Queue
template <typename t>
class ListQueue
{
    public:
        ListQueue();  //Default
        ~ListQueue(); //Destructor

        //Core Functions
        void insert(t data);  //AKA enqueue()
        t remove();     //AKA dequeue()

        //Aux/Helper Functions
        t peek();
        int getSize();
        bool isEmpty();
        void printQueue();

    private:
        DLL<t> *myQueue;

};

//Default Constructor
template <typename t>
ListQueue<t>::ListQueue() {
    myQueue = new DLL<t>();
}

//Destructor
template <typename t>
ListQueue<t>::~ListQueue() {
    delete myQueue;

    //cout << "Queue destructor called." << endl; //For debugging/testing
}

/************************************\
|           Core Functions           |
\************************************/

//Normal queue insert
template <typename t>
void ListQueue<t>::insert(t data) {
    myQueue->insertBack(data);
}

//Removes the front element of the queue and returns what was removed
template <typename t>
t ListQueue<t>::remove() {
    return myQueue->removeFront();
}

/****************************************\
|           Auxilary Functions           |
\****************************************/

//Returns the element at the front of the queue
template <typename t>
t ListQueue<t>::peek() {
    t temp = this->remove();
    myQueue->insertFront(temp); //Reinsert same value to the front of the queue.
    return temp;
}

//Returns the number of elements.
template <typename t>
int ListQueue<t>::getSize() {
    return myQueue->getSize();
}

//Checks if the queue is empty.
template <typename t>
bool ListQueue<t>::isEmpty() {
    return myQueue->isEmpty();
}

//Prints the queue using DBL's print function. For testing/debugging purposes.
template <typename t>
void ListQueue<t>::printQueue() {
    cout << "QUEUE SIZE: " << this->getSize() << endl;
    myQueue->printList(false);
}


#endif