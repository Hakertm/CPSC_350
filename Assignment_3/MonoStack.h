#ifndef MONOSTACK_H
#define MONOSTACK_H

#include "GenStack.h"

//Templated monotonically decreasing or increasing stack data structure
template<typename t>
class MonoStack : public GenStack<t> {
    public:
        MonoStack(); //Default constructor
        MonoStack(int maxSize, char o); //Overloaded constructor
        ~MonoStack(); //Destructor

        //Only function that is implemented differently
        void push(t data);

    private:
        char stackType;

};

//Default Constructor
template<typename t>
MonoStack<t>::MonoStack() {
    this->size = 64; //Default stack size
    this->top = -1;
    this->myArray = new t[this->size];
    stackType = 'd';
}

//Overloaded Constructor
template<typename t>
MonoStack<t>::MonoStack(int maxSize, char o) {
    //Check if parameter is correct.
    if(o != 'i' && o != 'd') {
        throw runtime_error("Invalid stack type parameter. Must be 'i' for increasing or 'd' for decreasing");
    }
    
    this->size = maxSize;
    this->top = -1;
    this->myArray = new t[this->size];
    stackType = o;
}

//Destructor
template<typename t>
MonoStack<t>::~MonoStack() {
    //cout << "MonoStack Obliterated!" << endl; //For testing
}

//Appends an item to the stack either monotonically increasing or decreasing.
template<typename t>
void MonoStack<t>::push(t data) {
    //Check if full
    if(this->isFull()) {
        throw runtime_error("Stack is full.");
    }

    //Automatically appends if stack is empty.
    if(this->isEmpty()) {
        this->top = this->top + 1;
        this->myArray[this->top] = data;
        return;
    }
    
    int initialSize = this->getSize();

    //Monotonically Increasing
    if(stackType == 'i') { 
        //Discards any elements that are greater than data, otherwise appends to the stack.
        for(int a = 0; a < initialSize; ++a) {
            
            //Check for duplicate.
            if(this->peek() == data) {
                return;
            }

            //Check if element is greater than data.
            if(this->peek() > data) { 
                this->pop();
            } else {
                this->top = this->top + 1;
                this->myArray[this->top] = data;
                return;
            }
        }

    //Monotonically Decreasing
    } else {
        //Discards any elements that are less than data, otherwise appends to the stack.
        for(int b = 0; b < initialSize; ++b) {
            
            //Check for duplicate.
            if(this->peek() == data) {
                return;
            }

            //Check if element is less than data.
            if(this->peek() < data) {
                this->pop();
            } else {
                this->top = this->top + 1;
                this->myArray[this->top] = data;
                return;
            }
        }
    }

    //Entire stack discarded
    this->top = this->top + 1;
    this->myArray[this->top] = data;
}

#endif