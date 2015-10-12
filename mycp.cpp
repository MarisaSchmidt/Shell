//
//  mycp.cpp
//  
//
//  Created by Marisa Schmidt on 1/23/15.
//
//

#include <iostream>
#include <stdio.h>
//Need to include the following, required in order to use open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//Need to include this, in order to use system call exit
#include <unistd.h>


using namespace std;

int main (int argc, char * argv[])
{
    
    int i;
    
    if (argc != 3) //too many or too little arguments
    {
        cout << "Usage: mycp src target\n";
        _exit(1);
    }
    
    //display all command line arguments
    //printf() to output to terminal
    printf ("mycp %s %s\n", argv[1], argv[2]);
    
    
    //STEP 1. make system call top open source file (given by arg[1]) to read
    int src_fd; //file descriptor for source file
    
    src_fd = open (argv[1], O_RDONLY);  //O_RDONLY is a constant defined in one of the header files, meaning we
    // are open the file to read (not to modify it)
    
    if (src_fd== -1) //error checking
    {
        cout << "Fails to open "<<argv[1]<<" to read\n";
        _exit (1);
    }
    
    
    //STEP 2. open argv[2], target file to write (truncate the file if it already exists)
    int dest_fd; //open target file to read
    dest_fd = open (argv[2], (O_WRONLY | O_CREAT));
    
    
    //STEP 3. enter a loop:
    //Read one byte a time from the file, and display the char on screen
    char buf;
    // as long as we are able to read a char from the source file,
    // write the char to target file
    while (read (src_fd, &buf, 1)==1)
    {
        write (dest_fd, &buf, 1)
    }
    
    
    //STEP 4. close both files. Always close the file descriptor, to deallocate os resource
    close (src_fd);
    close (dest_fd);
    
}
