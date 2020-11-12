/*
    CS 371: Programming Project
    Author: Brian Rowell
    Section 1

    This is the server program. 

*/
#include <stdio.h>
#include <sys/types.h> // def's of a number of data types used in system calls, these
                            // types are used in the next two include
#include <sys/socket.h> // def's of structures needed for sockets
#include <netinet/in.h> // constants and structures needed for internet domain addresses
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// put comments above in a read me bruh
// Remove any naked literals

// This function is called when a system call fails
// It prints a message and then terminates the program
// Citation: http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
void error(char *s) {
    perror(s);
    exit(1);
} // error()

// Main
int main(int argc, char *argv[]) {

    int sockfd, newsockfd; 
    // port number is just a random number between 2000 and 65535
    int port_number = 2001; // Stores the port number on which the server accepts connections
    int client_address_length; // Stores size of address of client 
    int n; // contains the number of characters read or written

    char buffer[256]; // server reads characters from the socket connection into this buffer

    // sockaddr_in is a struct containing an internet address
    struct sockaddr_in server_address, client_address;

    // socket(address domain, type of socket, protocol)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { 
        error("ERROR opening socket");
    }

    // Initialize server address to 0
    bzero((char *) &server_address, sizeof(server_address));

    // code for the address family, always set to AF_INET
    server_address.sin_family = AF_INET;
    // htons() converts port number in host byte order to a port number
    // in network byte order
    server_address.sin_port = htons(port_number);

    // IP Address of the Host
    // INADDR_ANY = IP address of the machine on which the server is running 
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind a socket to an address
    if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        error("ERROR on binding");
    }

    // Listen on the socket for connections
    listen(sockfd, 5);

    // accept() causes the process to block until a client connects to server
    client_address_length = sizeof(client_address);
    newsockfd = accept(sockfd, (struct sockaddr *) &client_address, 
        (socklen_t *) &client_address_length);
    if (newsockfd < 0) {
        error("ERROR on accept");
    }   

    // We only get to this point from a successful client connection

    // Create a file
    // Read in data and put into buffer
    n = read(newsockfd, buffer, 255);
    char *file_name = buffer;
    file_name[sizeof(file_name)] = '\0'; // there is no null terminating char for some reason
                                            // so I add it here
    printf("%s\n", file_name);

    /*
    char *new_file_path = strcat("test/output/", file_name);
    FILE *new_file = fopen(new_file_path, "w");
    bzero(buffer, 256);
    */

   /*
    while (1) {
        // Read in line from file and place into buffer
        n = read(newsockfd, buffer, 255);
        if (n < 0) {
            error("ERROR reading from socket");
        } else if (n == 0) {
            // n == 0 signifies we have no more characters to read in 
            break;
        }
        //printf("Here is the message: %s\n", buffer);

        // Write whatever's in buffer into new file
        fputs(buffer, new_file);
        bzero(buffer, 256);
    }

    n = write(newsockfd, "I got your message", 18);
    if (n < 0) {
        error("ERROR writing to socket");
    }
    */
    /*
    Steps:
        Wait for connection from the client
        Establish Connection
        Wait for files from client
        After disconnect from client, wait again until new client (aka while(1))

        should also be able to change IP address of server with command line user input

    */

    


    return 0;
}