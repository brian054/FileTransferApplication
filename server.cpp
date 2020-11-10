/*
    CS 371: Programming Project
    Author: Brian Rowell
    Section 1

    This is the server program. 

*/
#include <iostream>
#include <sys/types.h> // def's of a number of data types used in system calls, these
                            // types are used in the next two include
#include <sys/socket.h> // def's of structures needed for sockets
#include <netinet/in.h> // constants and structures needed for internet domain addresses

// This function is called when a system call fails
// It prints a message and then terminates the program
// Citation: http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
void error(string s) {
    cerr << s << endl;
    exit(0);
} // error()

// Main
int main(int argc, char *argv[]) {

    int sockfd, newsockfd; 
    // need this?
    int port_number; // Stores the port number on which the server accepts connections
    int client_address_length; // Stores size of address of client 
    int n; // contains the number of characters read or written

    // sockaddr_in is a struct containing an internet address
    struct sockaddr_in server_address, client_address;

    // socket(address domain, type of socket, protocol)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { // socket() returns -1 if the call fails
        error("ERROR opening socket");
    }

    

    return 0;
}