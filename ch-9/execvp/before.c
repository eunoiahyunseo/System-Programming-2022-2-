#include <unistd.h>
#include <stdio.h>

void main(void)
{
    char *arglist[2];

    int pid = getpid();

    arglist[0] = "./after";
    arglist[1] = NULL;

    printf("Before execvp(): %d\n", pid);

    execvp(arglist[0], arglist);
    return;
}