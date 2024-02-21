a. Erik Fryanov
b. 2365673
c. fryanov@chapman.edu
d. CPSC 350-03
e. Assignment 1

Note: Testing with the provided txt file from Slack caused the read in text to all be on one line
      even if there was a clear newline separation.
      Upon making a copy of said txt file, by directly copying the text from within the file to a
      brand new txt file, caused it to behave accordingly and read in the data with proper new line
      separation. For that reason, the included "original.txt" file is this said copy of the actual
      original text file.

To Compile(Linux/Docker):
g++ *.cpp

To Run(Linux/Docker):
./a.out

Resources Used:
--> Punctuation Check Method
https://www.programiz.com/cpp-programming/library-function/cctype/ispunct#:~:text=int%20ispunct(int%20ch)%3B,by%20the%20current%20C%20locale.

--> Whitespace Check Method
https://www.programiz.com/cpp-programming/library-function/cctype/isspace#:~:text=The%20isspace()%20function%20checks,feed%20(0x0c%2C%20'%5Cf')

--> Input/Output File Tutorial
https://cplusplus.com/doc/Tutorial/files/

--> Reset Input Stream Position
https://www.geeksforgeeks.org/set-position-with-seekg-in-cpp-language-file-handling/
