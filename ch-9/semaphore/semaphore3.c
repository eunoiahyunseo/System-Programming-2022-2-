#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>

int main()
{
    sem_t *sem;
    int i, work_t;
    int svalue;

    sem = sem_open("testsem", O_CREAT, 0644);
    sem_getvalue(sem, &svalue);
    printf("svalue : %d \n", svalue);

    srand(time(NULL));
    for (i = 0; i < 10; i++)
    {
        printf("Trying to get a semaphore ... \n");

        sem_wait(sem);

        work_t = rand() % 5 + 1;
        printf("Working for %d sec. \n", work_t);

        sleep(work_t);
        printf("\t\tDone. \n\n");

        sem_post(sem);
        sleep(1);
    }
}