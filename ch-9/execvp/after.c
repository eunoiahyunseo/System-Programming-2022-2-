#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int pid = getpid();
    printf("After execvp(): %d\n", pid);

    return 0;
}