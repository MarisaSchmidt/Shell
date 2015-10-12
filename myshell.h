//
//  myshell.h
//  
//
//  Created by Marisa Schmidt on 2/11/15.
//
//

#ifndef _myshell_h
#define _myshell_h

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>      // std::ifstream
using namespace std;

class Shell {
public:
    Shell();
    ~Shell();
    void prompt ();
    void isBatch(char *);
    void parse ();
    void print();
    void getToken (char *); //can make private or public
    int isExit();
   // bool isBackground();
    int execute ();
private:
    static const int MAX_LINE_LEN=1024; //each command line is at most 1023 character long
    int count;
    bool bckgrnd; //bool background
    char *cmdline;
    char **words; //number of arguments --> "words"

};


Shell::Shell() : cmdline(NULL), words(NULL), count(0), bckgrnd(false) { //constructor initializes variables
    cmdline = (char *) malloc (MAX_LINE_LEN);
    words = (char **) malloc (MAX_LINE_LEN);
    memset(cmdline, '\0', MAX_LINE_LEN); //initialize empty spaces to '\0' (program will find end of commandline before char 1024)
    memset(words, '\0', MAX_LINE_LEN);
    
};

Shell::~Shell () {
    free (cmdline);
    free (words);
    cmdline = NULL;
    words = NULL;
    
};
    
void Shell::prompt() {
    
    cout <<"[<<<(" << "user" <<"@"<< "host" <<" "<< "pwd"<<")>>>]: "; //display prompt message
    cin.getline(cmdline, MAX_LINE_LEN);
    
};

void Shell::isBatch(char * b_Line) {
    ifstream ifs(b_Line);
    string str;
    
    bool fluff = true; //to denote the extra stuff we don't need!
    
    //clean up , get rid of blank lines, comments
    do {
        char ch = ifs.peek(); //break line into char
        if (ch=='#') {
            ifs.ignore(MAX_LINE_LEN, '\n'); //ignore the rest of line if #
        } else {
            fluff = false;
        }
    } while ( fluff );
    
    
    while (ifs.peek() != EOF) { //read line
        getline(ifs, str); //getline
    }
           
    //copy line to cmdline (write line to cmdline)
    strcpy(cmdline, str.c_str());
    
};


void Shell::parse() {
    
    char *token = strtok(cmdline, " "); //first split;
    
    if (!token) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }
    else {
        
        int i = 0;

        while ((token) && (count < MAX_LINE_LEN)) { //if not at the end of line
            if ((strcmp(token,"&")) == 0) {
                *token = '\0';
                bckgrnd = true;
                
            } else {
                words[i] = strdup(token); //make a copy of the tokens from cmdline into array words[i]... this saves you the trouble of more complicated looping with and marking
                bckgrnd = false;
            }

            token = strtok (NULL, " "); //do not return pointer to beginnng of command line, but pick up where we left off
            i++;
            
            count = i; //update count
        }

    }//end else statement

    //let's clear rest of word array as we have all the tokens saved now and have reached end of command line

    if(bckgrnd==true){
        //*(words[count]) = '\0';
        count--; //increment count
     }
    
    free (token);
    token = NULL; //procedural.

};

void Shell::print() {
    for (int i=0; i<count; i++) {
        getToken (words[i]);
        //cout << " ";
    }
};

void Shell::getToken (char * token) {
    for (int i = 0; i < strlen(token); i++) {
        cout << token[i];
    }
};


int Shell::isExit() {
    if (strcmp (cmdline,"exit")==0) //is it an exit?
        return 0;
    else
        return 1;
};

/*
bool Shell::isBackground() {
    bool run;
    int i = strlen(cmdline)-2;
        if (cmdline[i] == '&')
            run = true;
        else
            run = false;
    
    return run;
};
 */

int Shell::execute() { //determine whether interactive mode or batch mode
    
    pid_t  pid;
    
    // is batch mode?
    if (words[0] != NULL) { //is interactive mode!

        /////// EXECUTE COMMAND LINE///////
        
        /* create a child process */
        
            pid = fork();
        //fork child process
            if (pid < 0) { /* error occurred in forking child process */
                fprintf(stderr, "Fork Failed");
                exit(-1);
            }
            else if (pid == 0) { /* child process forked*/
                //printf ("Child process ...\n");
                //Todo: checking return value of execvp...
                if (execvp(words[0], words) < 0) { //execute the command
                    printf("ERROR: Execution Failed\n");
                    
                }
                _exit(0);
            }
            else { /* parent process */
                /* parent will wait for the child to complete */
                if (bckgrnd==false){
                    wait (NULL);
                    
                }

            } //end else
    
        }//end if
    
    return 1; //return 1 regardless of whether it is interactive or batch mode
}





#endif
