/**
* psh1.c: prompting shell version 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define MAXARGS 20
#define ARGLEN 100

// use execvp to do it
int execute(char *arglist[]) {
    execvp(arglist[0], arglist);     // run it

    // if this -> execvp error ( and errno settled )
    perror("execvp failed");
    if(arglist != NULL) free(arglist);
    exit(1);
}

// trim off newline and create storage for the string
char *makestring(char *buf) {
    char *cp;
    buf[strlen(buf) - 1] = '\0'; // trim ( new line )

    // have to strlen(buf) + 1 becuase '\0' have to be included
    cp = malloc(strlen(buf) + 1); // get memory
    
    strcpy(cp, buf);
    return cp;
}

int main(int argc, char *argv[]) {
    char *arglist[MAXARGS + 1];
    
    int numargs;
    char argbuf[ARGLEN];
    
    numargs = 0;
    
    while(numargs < MAXARGS) {
        printf("Arg[%d] ? ", numargs);
        if(fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
            // argbuf -> "ls\n" -> strlen(argbuf) = 3
            arglist[numargs++] = makestring(argbuf); 
        else {
            if(numargs > 0) { // any args?
                arglist[numargs] = NULL;
                execute(arglist);
                numargs = 0;
            }
        }
    }

    return 0;
}