#include <stdio.h>
#include <signal.h>

void my_sig_handler(int signum)
{
    printf("signum = %d \n", signum);
    printf("signal is caught. \n");
    if (signum == SIGINT)
        // signal(SIGINT, SIG_IGN);
        signal(SIGINT, SIG_DFL);
}

int main(void)
{
    signal(SIGINT, my_sig_handler);
    signal(SIGUSR1, my_sig_handler);

    while (1)
    {
        printf("Hello \n");
        sleep(1);
    }

    return 0;
}