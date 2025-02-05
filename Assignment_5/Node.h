#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

//Node class storing data and pointer
template <typename t>
class Node {
    public:
        Node();
        Node(t d);
        ~Node();

        t data; //Can be any data type
        Node<t> *next;
        Node<t> *prev;
        
};

//Default Constructor
template <typename t>
Node<t>::Node() {
    next = NULL;
    prev = NULL;
}

//Overloaded Constructor
template <typename t>
Node<t>::Node(t d) {
    data = d;
    next = NULL;
    prev = NULL;
}

//Destructor
template <typename t>
Node<t>::~Node() {
    next = nullptr;
    prev = nullptr;

    //cout << "Node Destructor Called."<< endl; //For debugging/testing
}

#endif