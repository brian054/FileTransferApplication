/*
    CS 371: Programming Project
    Author: Brian Rowell
    Section 1

    This is the server program. 

*/
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <libgen.h> // for extracting file name https://linux.die.net/man/3/basename
/*

    Questions:
        Error control for path that specifies a directory instead of a file?

*/

// This function is called when a system call fails
// It prints a message and then terminates the program
// Citation: http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
void error(char *s) {
    perror(s);
    exit(1);
} // error()

// Main
int main(int argc, char *argv[]) {

    // This variable is a file descriptor that stores the value returned by the 
    // socket system call
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
    char *file_path = argv[2];
    FILE *myfile = fopen(file_path, "r");
    if (!myfile) {
        error("ERROR");
    } 

    // Extract the file name from the path given by the user
    // https://www.systutorials.com/how-to-get-the-directory-path-and-file-name-from-a-absolute-path-in-c-on-linux/
    char *file_name = basename(strdup(file_path));
    printf("%s \n", file_name);

    //ifstream my_file;
    //my_file.open(argv[2]);
    //if (my_file.fail()) {
    //    error("Error Opening File");
    //}

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    //server = gethostbyaddr(argv[1], sizeof(argv[1]), AF_INET);
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host \n");
        exit(0);
    }

    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &server_address.sin_addr.s_addr
                , server->h_length);
    server_address.sin_port = htons(port_number);

    if (connect(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        error("ERROR connecting");
    }

    // Give Server name of file
    //char file_name_buffer[strlen(file_name)];
    //bzero(file_name_buffer, strlen(file_name));
    
    // Put Name into Buffer
    //sprintf(file_name_buffer, "%s \n", file_name);
    //printf("File Name: %s \n", file_name_buffer);
    // write what's in buffer to server
    write(sockfd, file_name, strlen(file_name));

    /*
    // while not at end of file
    while (!feof(myfile)) {
        // Clear Buffer
        bzero(buffer, 256);
        // read a line from file and store it in buffer
        fgets(buffer, 255, myfile);
        // write that line to server
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0) {
            error("ERROR writing to socket");
        }
        /*
        bzero(buffer, 256);
        n = read(sockfd, buffer, 256);
        if (n < 0) {
        error("ERROR reading from socket");
        }
        printf("%s\n", buffer);
        
    }
    */
    return 0;
}