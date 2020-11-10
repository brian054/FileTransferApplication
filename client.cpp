/*
    CS 371: Programming Project
    Author: Brian Rowell
    Section 1

    This is the server program. 

*/
#include <iostream>

using namespace std;

// This function is called when a system call fails
// It prints a message and then terminates the program
// Citation: http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
void error(string s) {
    cerr << s << endl;
    exit(0);
} // error()

// Main
int main(int argc, char *argv[]) {

    // This variable is a file descriptor that stores the value returned by the 
    // socket system call
    int sockfd, port_number, n;

    if (argc < 3) { 
        cerr << "usage: " << argv[0] << " network_address file_path" << endl;
        return 0;
    }

    cout << argv[0] << endl;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    string file_path = argv[2];
    // Check and verify path is a valid path
    // try to fopen() or sum
    

    cout << argc << endl;

    return 0;
}