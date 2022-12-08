#include <stdio.h>
#include <signal.h>

int cnt = 0;
int pnum;
int pids[10];

// 2개의 프로세스가 barrier를 사용한다고 해 보자
// 그럼 cnt < 1
void my_sig_handler(int signum)
{
    // cnt로 몇개의 프로세스가 정착상태인지 count한다.
    cnt++;
}

void barrier()
{
    int i;

    // 다른 모든 프로세스에 SIGUSR1 시그널을 준다.
    // 만약 cnt가 pnum
    for (i = 0; i < pnum - 1; i++)
        kill(pids[i], SIGUSR1);

    if (cnt < pnum - 1)
    {
        // 시그널을 받을 때 까지 기다린다. -> 다른 프로세스에서 SUGUSR1 (=cnt++)
        pause();
    }

    // 만약 cnt == pnum - 1이면 그냥 넘어가서 다음 동작 수행
    // cnt 초기화를 해줘야 반복할 수 있다.
    cnt = 0;
}

int work(int sec)
{
    int i, j, k;
    int sum = 0;
    for (i = 0; i < sec; i++)
        // 대략 1초 걸리는 반복문을 작성했다.
        for (j = 0; j < 100; j++)
            for (k = 0; k < 1000000; k++)
                sum++;
}

int main()
{
    int i, work_t;
    printf("pid = %d \n", getpid());
    signal(SIGUSR1, my_sig_handler);
    printf("Enter the number of processes : ");
    scanf("%d", &pnum);

    // 자기 프로세스는 입력받지 않기 때문
    for (i = 0; i < pnum - 1; i++)
    {
        printf("Enter %d processes is : ", i);
        scanf("%d", &pids[i]);
    }

    while (1)
    {
        work_t = rand() % 10 + 1;
        printf("Working for %d secs... \n", work_t);
        work(work_t);
        printf("\t\t\t\t\t Done. \n");
        barrier();
        printf("End of barrier \n");
    }
}
