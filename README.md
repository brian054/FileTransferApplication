# File Transfer Application

## Course: CS 371
Author: Brian Rowell

### Note: The use of a percent sign '%' is to denote a command you would type into your command line interface. Do not include this percent sign when running the command, it is simply a symbol that denotes a command.

# To compile and run these programs:
  % gcc client.c -o runClient
  
  % gcc server.c -o runServer
  
  % ./runServer
  
  % ./runClient [hostname/IP address] [path to file]

  ## ./runClient takes two command line arguments
  1.) Hostname/IP address: 
  
  2.) Path: the path to the file you would like to transfer
  
  For example: "C:/Desktop/Files/demo.txt" is a possible path
  
### Note: Make sure you run the Server program BEFORE you run the Client program. If not, the Client program won't connect to the Server, as it is not running.

# Description:
  This project is a File Transfer Application. There are two programs to be run, the client and server programs.
  
###  Server:
    The server program is fairly straightforward. It waits for incoming connections from a client, receives the file name,
    creates the file and path, and then writes to that file what is receives from the client. 
    
    The server program uses a constant variable to set the IP address, therefore you can run this program on one machine, and the client
    program on another machine to send data between computers. 
  
###  Client:
    The client program connects to the server, sends the file name to the server, and then sends the server the data in 
    the file, line by line.
    
###  Output:
    The file that was transferred goes into an output folder. (Note: test whether running the program creates output folder or not)
    
Refereces:

