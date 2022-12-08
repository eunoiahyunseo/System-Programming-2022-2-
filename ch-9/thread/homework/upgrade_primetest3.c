#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int isPrime(int n)
{
    for (int i = 2; i <= n / 2; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int n;

int total_count = 0;
int testNum = 2;
sem_t *num_sem, *count_sem;

void *prime_count(void *arg)
{
    testNum++;
    int count = 0;
    int num;

    while (testNum <= n)
    {
        num = testNum;

        sem_wait(num_sem);
        testNum++;
        sem_post(num_sem);

        if (isPrime(num))
        {
            sem_wait(count_sem);
            total_count++;
            sem_post(count_sem);
        }
    }

    printf("Thread is done \n");
}

int main()
{
    int status;
    int count;

    num_sem = sem_open("num_sem", O_CREAT, 0644, 1); // init value is 1
    count_sem = sem_open("count_sem", O_CREAT, 0644, 1);
    pthread_t thrd1, thrd2;

    printf("Enter a positive integer : ");
    scanf("%d", &n);

    // function argument is void* -> char* form
    pthread_create(&thrd1, NULL, prime_count, NULL);
    pthread_create(&thrd2, NULL, prime_count, NULL);

    pthread_join(thrd1, &status);
    pthread_join(thrd2, &status);
    printf("The number of prime number is %d. \n", total_count);
}
