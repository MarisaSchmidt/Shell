//
// ADVANCED VERSION OF myshell.cpp
//  
//
//  Created by Marisa Schmidt on 2/9/15.
//
//

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
using namespace std;



                            //VARIABLES & DECLARATIONS
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------


//GLOBAL VARIABLES
const int MAX_LINE_LEN=1024; //each command line is at most 1023 characters long
const int WORD_LEN=51; //each word in the command line is at most 50 character long
const int MAX_WORD_NUM=20; //each command has at most 20 words in it ...


//needs to be global variable

//FUNCTION DECLARATIONS
void prompt();
char *read();
char **parse(char *);
int execute (char **);


                            //MAIN FUNCTION
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    int status;
    char *cmdline;
    char **args; //number of arguments --> "words"
    
    do {
        prompt();
        cmdline = read(); //read line
        args = parse(cmdline); //split command line into words
        status = execute(args); //execute words, commands
            //status determines when to exit
        free (cmdline);
        free (args);
        
    } while (status);
    
}

                            //FUNCTION DEFINITIONS
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------



//------------------------PROMPT FUNCTION--------------------------
void prompt() { //print prompt user
    char * pwd, * host, * usr;
    pwd = getenv ("PWD");
    host = getenv ("HOSTNAME");
    usr = getenv ("USER");
    
    cout <<"(" << usr <<"@"<<host<<" "<<pwd<<")>> "; //display prompt message
    
}


//------------------------READ FUNCTION--------------------------
char *read() { //read line
    
    //int bufsize = MAX_LINE_LEN;
    char *line = NULL;
    ssize_t bufsize = 0; //getline will allocate buffer

    getline(&line, &bufsize, stdin);
    return line;
}

//-------------------------PARSE FUNCTION-------------------------
//function to parse command line (split it up)
char **parse(char *cmdline) {
    
    char delim = '\0';
    int i = 0;
    int bufsize = MAX_LINE_LEN;
    char **words = malloc(bufsize * sizeof(char*));
    char *token;
    
    if (!words) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }
    else {
        
        token = strtok(cmdline, delim); //first split
        //returns pointer to the first token, placing '\0' at end of each token
        
        while ((token) && cmdline[i]!='\0') { //if not at the end of line
            
            words[i] = token;
            i++;
            
            if (i >= bufsize) { //in case line is longer than max_line_length
                bufsize += MAX_LINE_LEN;
                words = realloc(words, bufsize * sizeof(char*));
                
                if (!words) { //stop adding
                    fprintf(stderr, "allocation error\n");
                    exit(EXIT_FAILURE);
                }
            }
            
            
            token = strtok (NULL, delim);
        }
    }
    words[i] = NULL //null-terminated array of pointers
    return words;
    
}

      
//------------------------EXECUTE FUNCTION--------------------------
int execute(char **args) { //determine whether interactive mode or batch mode
   
    pid_t  pid;
    
    // is batch mode?
    if (args[0] == NULL) {
        return 1;
    }
    
    // is interactive mode?
    while (args[0]==1) {
    
        ///////WHAT DO I DO WITH THIS??///////
        if (!strcmp (cmdline,"exit")) //is it an exit?
            exit(0); //exit if it is
        
        ///////4. EXECUTE COMMAND LINE///////
        /* create a child process */
        
        pid = fork();
        //fork child process
        if (pid < 0) { /* error occurred in forking child process */
            fprintf(stderr, "Fork Failed");
            exit(-1);
            }
        else if (pid == 0) { /* child process forked*/
            printf ("Child process ...\n");
            
            //Todo: checking return value of execvp... 
            if (execvp(args[0], args) < 0) { //execute the command
                printf("ERROR: Execution of Fork Failed\n");
                exit (1);
                }
            else { /* parent process */
                /* parent will wait for the child to complete */
                wait (NULL);
                printf ("Child Complete");
                }
            }
    }
    return 1;
}
