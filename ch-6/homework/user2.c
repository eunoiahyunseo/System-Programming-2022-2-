#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int my_pid;
int user1_signum;
void my_sig_handler(int signum)
{
    printf("user1에게 시그널 전송.. \n");
    kill(user1_signum, SIGUSR1);
    sleep(1);
    kill(my_pid, SIGINT);
}

int main(void)
{
    signal(SIGUSR2, my_sig_handler);

    printf("my_pid = %d\n", (my_pid = getpid()));
    scanf("%d", &user1_signum);

    printf("------------------------\n");
    printf("user1로부터 SIGUSER2 기다리는중 ... \n");

    // for (;;)
    // {
    //     printf("..\n");
    //     sleep(5);
    // }

    pause();

    return 0;
}