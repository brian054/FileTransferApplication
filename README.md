# File Transfer Application

## Course: CS 371
Author: Brian Rowell

###### Note: The use of a percent sign '%' is to denote a command you would type into your command line interface. Do not include this percent sign when running the command, it is simply a symbol that denotes a command.

# To compile and run these programs:
  % gcc client.c -o runClient
  
  % gcc server.c -o runServer
  
  % ./runServer
  
  % ./runClient [hostname/IP address] [path to file]

  ## ./runClient takes two command line arguments
  1.) Hostname/IP address: the IP address you will use to connect to the server
  
  2.) Path: the path to the file you would like to transfer
  
  For example: "C:/Desktop/Files/demo.txt" is a possible path
  
###### Note: Make sure you run the Server program BEFORE you run the Client program. If not, the Client program won't connect to the Server, as it is not running.

# Description:
  This project is a File Transfer Application. There are two programs to be run, the client and server programs.
  
## Server:
   The server program is fairly straightforward. It waits for incoming connections from a client, 
   receives the file name, creates the file and path, and then writes to that file what is receives 
   from the client. 
    
   The server program uses a constant variable to set the IP address, therefore you can run this 
   program on one machine, and the client program on another machine given you are both connected
   to the same network.
  
##  Client:
   The client program connects to the server, sends the file name to the server, and then sends 
   the server the data in the file, line by line.
    
## Output:
   The file that was transferred goes into an output folder.
       
## More Notes:
### Error: Connection Refused
When running the client program, if you get an error message of "ERROR connecting: Connection refused" you most likely have the wrong Hostname/IP Address. To combat this issue, you can run the command 
  
  % hostname -I 
  
  to get your current IP Address ("hostname -I" will list more than one IP address if you are connected to Wifi AND Ethernet). If there are two addresses listed and you are unsure of which to use, I recommend going on your server's machine, running the hostname command, and then using that IP address in your command to run the client program (this is also assuming you are connected to one network on the server machine). 

### To Stop Server Program
The server program is designed to run forever. In theory, you would leave this server up forever and could upload files whenever you want.
To stop the program, simply press 'Ctrl' + 'C' (hold the ctrl key while pressing the c key) to kill the server program.

### Where does the transferred file go?
The transferred file is stored in a folder called output. This folder will be made in your current directory if it is not already made. Feel free to create the folder yourself, but my server program will do this for you if it is not present. 

### What port number should I use?
The server.c and client.c programs use port number 2001, so you do not have to worry about setting your own port number. If you would like to change
the port number, feel free to change the variable port_number in both the server.c and client.c files.

### Testing
To test this project I have provided some input files you can use. You can also come up with your own. 

# Refereces:
https://linux.die.net/man/3/basename : For extracting file name from path given by client

http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html : Socket Programming Tutorial

https://www.tutorialspoint.com/c_standard_library/c_function_system.htm : Introduced me to system() call 

https://linux.die.net/man/3/opendir : opendir() used to attempt to open output folder

https://www.tutorialspoint.com/cprogramming/c_file_io.htm : Referenced for File I/O

https://linux.die.net/man/3/htonl : For converting values between host and network byte order

https://linux.die.net/man/3/ntohl : For converting values between host and network byte order

https://linux.die.net/man/2/access : Used to check for file path existence

