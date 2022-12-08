#include <stdio.h>
#include <signal.h>

void siguser1(int n)
{
    printf("Oops! SIGNAL1!\n");
    kill(n, SIGSTOP);
}

void siguser2(int n)
{
    printf("Ooops! SIGNAL2!\n");
    kill(n, SIGKILL);
}

int main(void)
{
    int pid;
    signal(SIGUSR1, siguser1);
    signal(SIGUSR2, siguser2);
    pid = getpid();

    while (1)
    {
        printf("Hello\n");
        sleep(2);
    }
}