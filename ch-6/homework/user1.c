#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int my_pid;
int user2_signum;
void my_sig_handler(int signum)
{
    sleep(1);
    kill(my_pid, SIGINT);
}

int main(void)
{
    signal(SIGUSR1, my_sig_handler);

    printf("my_pid = %d\n", (my_pid = getpid()));
    scanf("%d", &user2_signum);

    printf("user2에게 시그널 전송\n");
    printf("------------------------\n");
    printf("user2로부터 SIGUSR1 기다리는중 ... \n");

    kill(user2_signum, SIGUSR2);

    // for (;;)
    // {
    //     printf("..\n");
    //     sleep(5);
    // }

    pause();

    return 0;
}