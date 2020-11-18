/*
    CS 371: Programming Project
    Author: Brian Rowell
    Section 1

    This is the client program. 

    Note: There are citations in the code itself, but I also include
    references in my README.md file.

*/
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <libgen.h> 

// This function is called when a system call fails
// It prints a message and then terminates the program
// Citation: http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
void error(char *s) {
    perror(s);
    exit(1);
} // error()

// Main
int main(int argc, char *argv[]) {

    // sockfd variable is a file descriptor that stores the value returned by the socket system call
    // n = number of character written or read
    int sockfd, port_number = 2001, n;
    struct sockaddr_in server_address;
    struct hostent *server;
    char buffer[256];

    // Making sure the user executes in the right format
    if (argc < 3) { 
        fprintf(stderr, "usage: %s network_address file_path\n", argv[0]);
        return 0;
    }

    // Check and verify file path is valid
    // I use access() here instead of fopen() due to an unknown error that kept popping up in my file transfers
    // when opening the file here. access() checks whether the process can access the file in file_path
    // Citation: https://linux.die.net/man/2/access
    char *file_path = argv[2];
    if (access(file_path, F_OK) != 0) {
        error("ERROR");
    }
    
    // Extract the file name from the path given by the user
    char *file_name = basename(strdup(file_path));
    
    // Create a new socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    // You could also use 
    // server = gethostbyaddr(argv[1], sizeof(argv[1]), AF_INET);
    // Retrieve server name
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host \n");
        exit(0);
    }

    // Set the fields in serv_addr
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &server_address.sin_addr.s_addr
                , server->h_length);
    server_address.sin_port = htons(port_number);

    // Establish connection to server
    if (connect(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        error("ERROR connecting");
    }

    // At this point we have connected to server
    printf("Connected to Server.... \n");

    // Give the server the name of the file
    int file_size_characters = strlen(file_name);
    int converted_file_size = htonl(file_size_characters);
    write(sockfd, &converted_file_size, sizeof(converted_file_size));
    write(sockfd, file_name, strlen(file_name));
    
    // Open our file to send
    FILE *myfile = fopen(file_path, "r");
    if (!myfile) {
        error("ERROR");
    }  

    // while we have not reached end of file
    while (!feof(myfile)) {
        // Clear the buffer
        bzero(buffer, 256);
        // read a line from file and store it in buffer
        fgets(buffer, 256, myfile);
        // write that line to server
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            error("ERROR writing to socket");
        }
    }
    // Close the file once finished writing
    fclose(myfile);

    printf("File Sent.... \n");
    printf("Connection ended.... \n");
    
    return 0;
}