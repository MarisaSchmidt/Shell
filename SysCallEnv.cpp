//
//  SysCallEnv.cpp
//  
//
//  Created by Marisa Schmidt on 2/19/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include<iostream>
using namespace std;

char fn[128], err_buffer[256];

int main (int argc, char *argv[])
{
    
    int pid, ppid;
    char *envptr;
    
    if (argc==1||(((argc-1)%2)!=0)) { //if argc is not odd (to except groups of two), or there are not enough arguments, ERROR.
        printf("ERROR : Usage : %s <env variable>\n", argv[0]);
        return -1;
    }
    
    
    for (int i=1; i < argc; i+=2) {  //not at end of command line
        
        strcpy (fn, argv[i]); //get file name
        int fd;
        fd = open( fn, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR); //use file to open file name
        
        if (fd == -1) //writing failed
        {
            sprintf(err_buffer, "ERROR : Can not open %s for write\n", fn);
            perror(err_buffer);
            return -1;
        }
        
        envptr = getenv(argv[i+1]); //get environment variable and have envptr point to it
        
        write(fd, argv[i+1], strlen(argv[i+1])); //first, write environment variable to file
        write(fd, " = ", 3); // allow space for aesthetics
        
        if (write(fd, envptr, strlen(envptr)) == -1)
        {
            printf("ERROR : Can not write to file %s\n", fn);
            // return -1;
        }
        
        write (fd, "\n", 2); //for aesthetics
        
        if (close(fd) == -1)
            perror("Can not close the file!\n");
        
    }
}
