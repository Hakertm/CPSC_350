a. Erik Fryanov
b. 2365673
c. fryanov@chapman.edu
d. CPSC 350-03
e. Assignment 5 

Compile(Linux/Docker):
g++ *.cpp

Run(Linux/Docker):
./a.out


Note 1: Memory leak in Faculty class as the dynamically allocated DLL isn't deleted due to double
        freeing problems encountered in the Database class implementation.

Note 2: Rebalance function in the LBST disabled as a segmentation fault was occuring that could
        not be resolved. If that segmentation fault never occured, then rebalance function would
        work as it should except if there were an even number of nodes being rebalanced (one of
        the nodes would be reinserted again, and another wouldn't be reinserted at all). 

[-----------------------------]

Resources Used:
--> General Info about Operator Overloading
https://www.geeksforgeeks.org/operator-overloading-cpp/

--> Operator Overloading Example
https://www.learncpp.com/cpp-tutorial/overloading-the-comparison-operators/

--> Operator Overloading Troubleshooting
https://stackoverflow.com/questions/16291623/operator-overloading-c-too-many-parameters-for-operation

--> Insertion Operator Overloading
https://learn.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170

--> Getline function Info
https://www.geeksforgeeks.org/getline-string-c/#

--> Check if input is integer.
https://www.geeksforgeeks.org/program-check-input-integer-string/

--> Max tree depth code
https://www.geeksforgeeks.org/find-the-maximum-depth-or-height-of-a-tree/#
