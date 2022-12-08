#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int pid, sig_num, result;
    if (argc != 3)
    {
        printf("Needs pid signum\n");
        exit(0);
    }
    pid = atoi(argv[1]);
    sig_num = atoi(argv[2]);
    result = kill(pid, sig_num);
    printf("result = %d\n", result);
}