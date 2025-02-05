#ifndef DBLLIST_H
#define DBLLIST_H

#include <string>
#include <exception>

#include "Node.h"

//Double Linked list class with various operations
template <typename t>
class DLL {
    public:
        DLL();
        ~DLL();

        //Core functions
        void insertFront(t d); //AKA prepend()
        void insertBack(t d);  //AKA append()
        t removeFront();
        t removeBack();
        t removeNode(t value); //Data type must be same as Node's
        t find(t value);       //Data type must be same as Node's
        bool isEmpty();
        int getSize();
        string returnData();

        // //Helper function
        // void printList(bool printLink);

    private:
        Node<t> *front;
        Node<t> *back;
        int size;

};

//Default constructor
template <typename t>
DLL<t>::DLL() {
    front = NULL;
    back = NULL;
    size = 0;
}

//Destructor
template <typename t>
DLL<t>::~DLL() {
    Node<t> *node = front;
    Node<t> *nodeToBeDeleted = front;
    while(node != NULL) {
        nodeToBeDeleted = node->next;
        delete node;
        node = nodeToBeDeleted;
    }

    //cout << "DLL Destructor Called." << endl; //For debugging/testing
}

//Inserts node at the front of the list
template <typename t>
void DLL<t>::insertFront(t d) {
    Node<t> *node = new Node<t>(d);

    if(isEmpty()) {
        back = node;
    } else {
        //Not empty
        node->next = front;
        front->prev = node;
    }

    front = node;
    ++size;
}

//Inserts node at the back of the list
template <typename t>
void DLL<t>::insertBack(t d) {
    Node<t> *node = new Node<t>(d);

    if(isEmpty()) {
        front = node;
    } else {
        //Not empty
        node->prev = back;
        back->next = node;
    }

    back = node;
    ++size;
}

//Removes the node at the front.
template <typename t>
t DLL<t>::removeFront() {
    if(isEmpty()) {
        throw runtime_error("List is empty.");
    }

    Node<t> *temp = front;

    //If only one node in list
    if(front->next == NULL) {
        back = NULL;
    } else {
        //Node to be removed is not the only node
        front->next->prev = NULL;
    }

    front = front->next;
    temp->next = NULL;
    t data = temp->data;
    --size;
    delete temp;

    return data;
}

//Removes node at the back of the list
template <typename t>
t DLL<t>::removeBack() {
    if(isEmpty()) {
        throw runtime_error("List is empty.");
    }

    Node<t> *temp = back;

    //If only one node in list
    if(back->prev == NULL) {
        front = NULL;
    } else {
        //Node to be removed is not the only node
        back->prev->next = NULL;
    }

    back = back->prev;
    temp->prev = NULL;
    int data = temp->data;
    --size;
    delete temp;

    return data;
}

//Searches entire list for the input value.
template <typename t>
t DLL<t>::find(t value) {
    Node<t> *curr = front;

    while(curr != NULL) {
        if(curr->data == value) {
            return curr->data;
        }
        curr = curr->next;
    }

    return -1; //Not found
}

//Removes a node from the list
template <typename t>
t DLL<t>::removeNode(t value) {
    //Check if empty
    if(isEmpty()) {
        throw runtime_error("List is empty.");
    }

    //Find the node
    Node<t> *curr = front;
    while(curr->data != value) {
        curr = curr->next;

        if(curr == NULL) {
            return -1;
        }
    }

    //4 conditions. If node is at the front, back, in between, or if the list is of size 1.
    if(size == 1) {
        front = NULL;
        back = NULL;
    } else if(curr == front) {
        front = curr->next;
        front->prev = NULL;
    } else if(curr == back) {
        back = curr->prev;
        back->next = NULL;
    } else {
        //Node between front and back
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }

    curr->next = NULL;
    curr->prev = NULL;
    int temp = curr->data;
    --size;
    delete curr;

    return temp;
}

//Returns the size of the doubly linked list.
template <typename t>
int DLL<t>::getSize() {
    return size;
}

//Checks if the list is empty
template <typename t>
bool DLL<t>::isEmpty() {
    return (size == 0);
}

//Returns the data at each node in the linked list.
template <typename t>
string DLL<t>::returnData() {
    Node<t> *curr = front;
    string contents = "";
    
    //Iterates through the whole list.
    while(curr != NULL) {
        contents += to_string(curr->data) + "\n";
        curr = curr->next;
    }

    return contents;
}

// //Prints the linked list and all nodes to the console. For debugging/testing.
// template <typename t>
// void DLL<t>::printList(bool printLink) {
//     Node<t> *curr = front;
    
//     while(curr != NULL) {
//         if(curr == front) {
//             cout << "{FRONT}: ";
//         } else if(curr == back) {
//             cout << "{REAR}: ";
//         } if(printLink) {
//             cout << "[ PREV: "<< curr->prev << " || " << curr->data << " || NEXT: "<< curr->next << " ] ";
//         } else {
//             cout << "[ " << curr->data << " ] ";
//         }

//         curr = curr->next;
//         if(curr != NULL){
//             cout << " <==> ";
//         }
//     }

//     cout << endl;
// }

#endif