//
//  myshell.cpp
//  
//
//  Created by Marisa Schmidt on 2/11/15.
//
//

#include "myshell.h"
#include<iostream>


int main(int argc, char * argv[]) {

    int status;
    
    do {
        
        Shell shell;
                               
        if (argc > 1) //BATCH MODE
        {
            status = 0;
            shell.isBatch(argv[1]);
        }
        else { //INTERACTIVE MODE
            shell.prompt(); //get user input, prompt user
           
        }
        
        //PROCESS
        shell.parse(); //split command line into words
       // shell.print(); //print what user entered
        
        //USER EXIT?
        if (shell.isExit()==0)
            status = 0;
        else
            status = shell.execute(); //execute words, commands
    
    } while (status == 1); //status determines when to exit
    
    return 0;
}
