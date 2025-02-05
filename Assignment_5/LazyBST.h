#ifndef LAZYBST_H
#define LAZYBST_H

#include "DBlList.h"
#include <iostream>
#include <fstream>

using namespace std;

//Templated TreeNode Class
template <typename T>
class TreeNode {
    public:
        TreeNode();
        TreeNode(T k);
        virtual ~TreeNode();

        T key; //key = data
        TreeNode<T> *left;
        TreeNode<T> *right;
        int leftDepth;
        int rightDepth;

};

//Default TreeNode Constructor
template <typename T>
TreeNode<T>::TreeNode() {
    left = NULL;
    right = NULL;
    key = NULL;
    leftDepth = 0;
    rightDepth = 0;
}

//Overloaded TreeNode Constructor
template <typename T>
TreeNode<T>::TreeNode(T k) {
    left = NULL;
    right = NULL;
    key = k;
    leftDepth = 0.0;
    rightDepth = 0.0;
}

//TreeNode Destructor
template <typename T>
TreeNode<T>::~TreeNode() {
    left = NULL;
    right = NULL;

    //cout << "TreeNode Destructor Called." << endl;
}


/****************************************\
|             Lazy BST Class             |
\****************************************/

//Templated Lazily Balanced Binary Search Tree Class
template <typename T>
class LazyBST {
    public:
        LazyBST(); //Initializes an Empty Tree
        virtual ~LazyBST();
        void recDelete(TreeNode<T> *node); //Destructor Helper Function

        //Core Functions
        void insert(T value);
        T* search(T value);     
        bool contains(T value); 
        bool deleteNode(T k);
        TreeNode<T> *getSuccessor(TreeNode<T> *d); //deleteNode Helper Function

        //Auxilary Functions
        bool isEmpty();
        T getMin();
        T getMax();
        int getNumNodes();
        T* getRoot();

        //Print Functions
        void outputTree(ostream& outS);
        void recOutput(ostream& outS, TreeNode<T> *node);
        void printTree();
        void recPrint(TreeNode<T> *node);

    private:
        TreeNode<T> *root;
        int numNodes;

        void rebalance(); 

        //Helper functions
        void getNodesInorder(TreeNode<T>* node, DLL<T>* list);
        void calcNodeDepths(TreeNode<T>* node);
        int calcDepth(TreeNode<T> *node);
    
};

//Default LazyBST Constructor
template <typename T>
LazyBST<T>::LazyBST() {
    root = NULL;
    numNodes = 0;
}

//LazyBST Destructor
template <typename T>
LazyBST<T>::~LazyBST() {
    this->recDelete(root);

    //cout << "Lazy BST Destructor Called." << endl;
}

//Helper function for the destuctor. Recursively deletes nodes using post order traversal.
template <typename T>
void LazyBST<T>::recDelete(TreeNode<T> *node) {
    if(node == NULL) {
        return;
    }

    this->recDelete(node->left);
    this->recDelete(node->right);
    delete node;
}


/****************************************\
|           Core BST Functions           |
\****************************************/

//Inserts a node into the LazyBST.
template <typename T>
void LazyBST<T>::insert(T value) {
    TreeNode<T> *node = new TreeNode<T>(value);

    if(isEmpty()) {
        root = node;
    } else {
        //Tree has 1 or more nodes
        TreeNode<T> *current = root;
        TreeNode<T> *parent = root;

        //Traverses the tree
        while(true) {
            parent = current;

            if(value < current->key) {
                //Go left
                current = current->left;
                
                //Found insertion point
                if(current == NULL) {
                    parent->left = node;
                    break;
                }

            } else {
                //Go right
                current = current->right;

                //Found insertion point
                if(current == NULL) {
                    parent->right = node;
                    break;
                }
            }
        }

    }

    numNodes++;

    //Recalculate depths and check if the tree needs to be rebalanced.
    this->calcNodeDepths(root);
    this->rebalance();

}

//Searches the tree for the value
template <typename T>
T* LazyBST<T>::search(T value) {
    //Checks if the tree is empty
    if(isEmpty()) {
        return NULL;
    }

    TreeNode<T> *current = root;

    //Traverse tree in search of value
    while(current->key != value) {
        if(value < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }

        //Value not found
        if(current == NULL) {
            return NULL;
        }
    }

    return &(current->key);
}

//Checks whether or not the value is in the tree.
template <typename T>
bool LazyBST<T>::contains(T value) {
    //Checks if the tree is empty
    if(isEmpty()) {
        return false;
    }

    TreeNode<T> *current = root;

    //Traverse tree in search of value
    while(current->key != value) {
        if(value < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }

        //Value not found
        if(current == NULL) {
            return false;
        }
    }

    return true;
}

//Deletes a node in the LazyBST
template <typename T>
bool LazyBST<T>::deleteNode(T k) {
    //Checks if the tree is empty
    if(isEmpty()) {
        return false;
    }

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeft = true;
    
    //Find node to delete to traverse tree
    while(current->key != k) {
        parent = current;

        if(k < current->key) {
            isLeft = true;
            current = current->left;
        } else {
            isLeft = false;
            current = current->right;
        }

        if(current == NULL) {
            return false;
        }
    }

    //If we make it here, that means the node is found
    
    //CASE 1 (LEAF NODE)
    //No children, so node is a leaf node.
    if(current->left == NULL && current->right == NULL) {
        if(current == root) {
            root = NULL;
        } else if(isLeft) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
    }

    //CASE 2 (HAS 1 [LEFT] CHILD)
    //Node has one LEFT child.
    else if(current->right == NULL) {
        if(current == root) {
            root = current->left;
        } else if(isLeft) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
    }

    //CASE 2 (HAS 1 [RIGHT] CHILD)
    //Node has one RIGHT child.
    else if(current->left == NULL) {
        if(current == root) {
            root = current->right;
        } else if(isLeft) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
    }

    //CASE 3 (HAS 2 CHILDREN)
    //Node has two children.
    else {
        TreeNode<T> *successor = getSuccessor(current);

        if(current == root) {
            root = successor;
        } else if(isLeft) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }

        successor->left = current->left;
        current->left = NULL;
        current->right = NULL;
    }
    
    delete current;
    numNodes--;

    //Recalculate depths and check if the tree needs to be rebalanced.
    this->calcNodeDepths(root);
    this->rebalance();

    return true;
}

//Finds the successor
//Note: d is the node to be deleted.
template <typename T>
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T> *d) {
    TreeNode<T> *sp = d; //Successor parent
    TreeNode<T> *succesor = d;
    TreeNode<T> *current = d->right;

    while(current != NULL) {
        sp = succesor;
        succesor = current;
        current = current->left;
    }

    //Successor found. Need to check if the successor is a descendant of the right child.
    if(succesor != d->right) {
        sp->left = succesor->right;
        succesor = current->left;
    }

    return succesor;
}


/****************************************\
|         Auxilary BST Functions         |
\****************************************/

//Checks if the tree is empty
template <typename T>
bool LazyBST<T>::isEmpty() {
    return (root == NULL);
}

//Gets the smallest value in the tree
template <typename T>
T LazyBST<T>::getMin() {
    //Checks if the tree is empty
    if(isEmpty()) {
        return NULL;
    }

    TreeNode<T> *current = root;

    //Iterates until final leaf node is reached on the left
    while(current->left != NULL) {
        current = current->left;
    }

    return current->key;

}

//Gets the largest value in the tree
template <typename T>
T LazyBST<T>::getMax() {
    //Checks if the tree is empty
    if(isEmpty()) {
        return NULL;
    }

    TreeNode<T> *current = root;

    //Iterates until the final leaf node is reached on the right
    while(current->right != NULL) {
        current = current->right;
    }

    return current->key;

}

//Gets the number of nodes.
template <typename T>
int LazyBST<T>::getNumNodes() {
    return numNodes;
}

//Gets the root node.
template <typename T>
T* LazyBST<T>::getRoot() {
    return &(root->key);
}

/****************************************\
|          Print BST Functions           |
\****************************************/

//Outputs the trees contents to a file.
template <typename T>
void LazyBST<T>::outputTree(ostream& outS) {
    this->recOutput(outS, root);
}

//Helper function for outputTree()
template <typename T>
void LazyBST<T>::recOutput(ostream& outS, TreeNode<T> *node) {
    //End condition
    if(node == NULL) {
        return;
    }
    
    //Inorder traversal
    this->recOutput(outS, node->left);
    outS << node->key;
    this->recOutput(outS, node->right);
    
}

//Prints entire tree starting from the root (see recPrint())
template <typename T>
void LazyBST<T>::printTree() {
    this->recPrint(root);
}

//Prints nodes starting from node with in order traversal
template <typename T>
void LazyBST<T>::recPrint(TreeNode<T> *node) {
    //End condition
    if(node == NULL) {
        return;
    }
    
    // //Inorder traversal
    // this->recPrint(node->left);
    // cout << node->key << endl;
    // // cout << "Left: " << node->leftDepth << " Right: "<< node->rightDepth << endl; //For debugging and testing.
    // this->recPrint(node->right);

    //Preorder Traversal, for testing/debugging
    cout << node->key << endl;
    this->recPrint(node->left);
    this->recPrint(node->right);

}


/****************************************\
|           Rebalance Function           |
\****************************************/

//Rebalances the tree to be as perfectly balanced as possible.
template <typename T>
void LazyBST<T>::rebalance() {
    int depthDif = abs(root->leftDepth - root->rightDepth);
    
    //Check if the tree needs to be rebalanced. Only rebalances if the difference is greater than 2.
    if(depthDif < 2) {
        return;
    }

    // //Get all the nodes in ascending order to insert into an array.
    // DLL<T>* tempList = new DLL<T>();

    // this->getNodesInorder(root, tempList);

    // //Put all nodes into an array of size numNodes in ascending order.
    // int size = numNodes;
    // T* nodes = new T[size];
    
    // for(int i = 0; i < size; ++i) {
    //     nodes[i] = tempList->removeFront();
    // }
    
    // //Delete tree nodes to prep for reinsertion.
    // this->recDelete(root); 

    // //Reinserts data based on the LBST algorithm.
    // for(int i = 0; i < size; ++i) {
    //     if((i % 2) == 0) {
    //         int median = (size - i)/2;
    //         this->insert(nodes[median]);
    //     } else {
    //         int median = (size + i)/2;
    //         this->insert(nodes[median]);
    //     }
    // }

    // delete nodes;
    // delete tempList;

}


/****************************************\
|          Helper BST Functions          |
\****************************************/

//Inserts nodes into a list in ascending order
template <typename T>
void LazyBST<T>::getNodesInorder(TreeNode<T>* node, DLL<T>* list) {
    //End condition
    if(node == NULL) {
        return;
    }

    //Inorder traversal
    getNodesInorder(node->left, list);
    list->insertBack(node->key);
    getNodesInorder(node->right, list);

}

//Calculates the left and right subtree depths at each node
template <typename T>
void LazyBST<T>::calcNodeDepths(TreeNode<T>* node) {
    if(node == NULL) {
        return;
    }

    //Calculate the depths for the left and right subtrees
    int leftD = calcDepth(node->left);
    int rightD = calcDepth(node->right);

    //Assign calculated heights to the node.
    node->leftDepth = leftD + 1;
    node->rightDepth = rightD + 1;

    //Traverse through the entire tree.
    calcNodeDepths(node->left);
    calcNodeDepths(node->right);

}

//Source for this Code: https://www.geeksforgeeks.org/find-the-maximum-depth-or-height-of-a-tree/#
//Calculates the left and right depth of the node.
template <typename T>
int LazyBST<T>::calcDepth(TreeNode<T>* node) {
    //End condition.
    if (node == NULL) {
        return 0;
    }
        
    //Traverse and calculate tree depth.
    int lDepth = calcDepth(node->left);
    int rDepth = calcDepth(node->right);
 
    //Return the larger value.
    if (lDepth > rDepth) {
        return (lDepth + 1);
    } else {
        return (rDepth + 1);
    }
}

#endif