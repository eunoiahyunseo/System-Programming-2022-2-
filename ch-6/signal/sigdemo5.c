#include <stdio.h>
#include <signal.h>

void my_sig_handler(int signum)
{
    printf("handler is activate \n");

    if (signum == SIGALRM)
    {
        printf("My alarm handler. \n");
        alarm(5);
    }
    else if (signum == SIGUSR1 || signum == SIGUSR2)
        printf("my SIGUSR handler");
}

int main(void)
{

    signal(SIGALRM, my_sig_handler);
    signal(SIGUSR1, my_sig_handler);
    signal(SIGUSR2, my_sig_handler);

    alarm(5);

    while (1)
    {
        printf("Hello\n");

        sleep(1);
    }

    return 0;
}