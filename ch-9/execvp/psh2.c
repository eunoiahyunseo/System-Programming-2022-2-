/**
 * psh1.c: prompting shell version 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXARGS 20
#define ARGLEN 100

int execute(char **);
char *makestring();

int main(int argc, char *argv[])
{
    char *arglist[MAXARGS + 1]; // an aray of ptrs
    int numargs;                // index into array
    char argbuf[ARGLEN];        // read stuff here

    numargs = 0;
    while (numargs < MAXARGS)
    {
        printf("Arg[%d] ? ", numargs);
        if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
            // argbuf -> "ls\n" -> strlen(argbuf) = 3
            arglist[numargs++] = makestring(argbuf);
        else
        {
            if (numargs > 0)
            {                            // any args?
                arglist[numargs] = NULL; // close list
                execute(arglist);        // do it
                numargs = 0;             // and reset for shell
            }
        }
    }

    return 0;
}

// use fork and execvp and wait to do it
int execute(char *arglist[])
{
    int pid, exitstatus; // of child
    pid = fork();
    switch (pid)
    {
    case -1:
        perror("fork failed.");
        exit(1); // from stdlib.h
    case 0:
        execvp(arglist[0], arglist); // do it

        // error control
        perror("execvp failed");
        exit(1);
    default:
        while (wait(&exitstatus) != pid)
            ;                                                                              // wait until
        printf("child exited with status %d, %d \n", exitstatus >> 8, exitstatus & 03777); // octal code
    }
}

// trim off newline and create storage for the string
char *makestring(char *buf)
{
    char *cp;
    buf[strlen(buf) - 1] = '\0'; // trim ( new line )

    // have to strlen(buf) + 1 becuase '\0' have to be included
    cp = malloc(strlen(buf) + 1); // get memory

    strcpy(cp, buf);
    return cp;
}
