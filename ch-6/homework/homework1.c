#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

int my_sig_handler2(int signum)
{
    printf("나 죽었어\n");
    kill(getpid(), SIGKILL);
}

int my_sig_handler3(int signum)
{
    return 0;
}

int my_sig_handler(int signum)
{
    printf("프로그램이 죽습니다.\n");
    kill(getpid(), SIGUSR1);
}

// 함수를 호출할 때마다 현재 시간을 갱신해 주어야 한다.
void print_current_time(struct tm *tm)
{
    time_t ct;
    ct = time(NULL);
    *tm = *localtime(&ct);
    int count = 0;
    printf("hyunseo: %d-%d-%d hour: %d, min : %d, sec: %d\n",
           (*tm).tm_year + 1900, (*tm).tm_mon + 1, (*tm).tm_mday, (*tm).tm_hour,
           (*tm).tm_min, (*tm).tm_sec);
}
int main()
{
    time_t ct;
    struct tm tm;
    ct = time(NULL);
    int count = 0;
    signal(SIGALRM, my_sig_handler);
    signal(SIGUSR1, my_sig_handler2);
    signal(SIGSEGV, my_sig_handler3);

    while (++count)
    {
        print_current_time(&tm);
        if (count == 3)
            alarm(1);

        sleep(2);
    }
}