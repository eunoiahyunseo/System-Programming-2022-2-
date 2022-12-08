#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void f(int num) { printf("OUCH!\n"); }

int main(void)
{
    void f(int);
    int i;
    signal(SIGINT, f);
    // signal(SIGINT, SIG_IGN);

    // printf("you can't stop me!\n");

    for (i = 0;; i++)
    {
        sleep(1);
        // printf("hello\n");
        printf("haha\n");
    }
}