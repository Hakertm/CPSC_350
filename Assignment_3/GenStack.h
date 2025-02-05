#ifndef GENSTACK_H
#define GENSTACK_H

#include <iostream>
#include <exception>
using namespace std;

//Generic stack class using string data type
template <typename t>
class GenStack {
    public:
        GenStack(); //Default constructor
        GenStack(int maxSize); //Overloaded constructor
        virtual ~GenStack(); //Destructor

        //Core Functions
        virtual void push(t data); //Overriden in MonoStack
        virtual t pop();

        //Auxilary Functions
        virtual t peek(); //AKA top()
        virtual bool isEmpty();
        virtual bool isFull();
        virtual int getSize();

    protected:
        t *myArray;
        int top;
        int size;

};

//Default Constructor
template<typename t>
GenStack<t>::GenStack() {
    size = 64; //Default stack size
    top = -1;
    myArray = new t[size];
}

//Overloaded Constructor
template<typename t>
GenStack<t>::GenStack(int maxSize) {
    size = maxSize;
    top = -1;
    myArray = new t[size];
}

//Destructor
template<typename t>
GenStack<t>::~GenStack() {
    delete[] myArray;

    //cout << "Stack Obliterated!" << endl; //For testing
}

/************************************\
|           Core Functions           |
\************************************/

//Appends to the top of the stack but with resizing capabilities
template<typename t>
void GenStack<t>::push(t data) {
    //Check if full
    if(isFull()) {
        
        cout << "Stack resizing..." << endl;
        
        t *temp = new t[2 * size];
        
        //Copy data from old array to new array
        for(int i = 0; i < size; ++i) {
            temp[i] = myArray[i];
        }
        
        size *= 2; //Update size
        delete[] myArray; //Delete old array
        myArray = temp; //Point to new array

    }
    
    myArray[++top] = data; //Pre-increment
}

//Removes item from top of the stack
template<typename t>
t GenStack<t>::pop() {
    //Check if empty
    if(isEmpty()) {
        throw runtime_error("Stack is empty.");
    }

    return myArray[top--]; //Post-decrement
}

/****************************************\
|           Auxilary Functions           |
\****************************************/

//Returns top item of the stack
template<typename t>
t GenStack<t>::peek() {
    //Check if empty
    if(isEmpty()) {
        throw runtime_error("Stack is empty.");
    }
    return myArray[top];
}

//Checks if the stack is empty
template<typename t>
bool GenStack<t>::isEmpty() {
    return (top == -1);
}

//Checks if the stack is full
template<typename t>
bool GenStack<t>::isFull() {
    return (top == (size - 1));
}

//Returns how many items are in the stack
template<typename t>
int GenStack<t>::getSize() {
    return top + 1;
}

#endif