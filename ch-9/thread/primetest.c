#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int isPrime(int n)
{
	for (int i = 2; i <= n / 2; i++)
		if (n % i == 0)
			return 0;

	return 1;
}

int N;
void *prime_count1(void *arg)
{
	int count = 0;
	int *ptr = (int *)malloc(sizeof(int));
	for (int i = 2; i <= N / 2; i++)
		if (isPrime(i))
			count++;

	*ptr = count;
	pthread_exit(ptr);
}

void *prime_count2(void *arg)
{
	int count = 0;
	int *ptr = (int *)malloc(sizeof(int));

	for (int i = N / 2 + 1; i <= N; i++)
		if (isPrime(i))
			count++;

	*ptr = count;
	pthread_exit(ptr);
}

int main()
{
	int count = 0;
	void *status;
	pthread_t thrd1, thrd2;

	printf("Enter a positive integer : ");
	scanf("%d", &N);
	pthread_create(&thrd1, NULL, prime_count1, NULL);
	pthread_create(&thrd2, NULL, prime_count2, NULL);

	pthread_join(thrd1, &status);
	printf("status = %d \n", *(int *)status);
	count += *(int *)status;
	free(status);

	pthread_join(thrd2, &status);
	printf("status = %d \n", *(int *)status);
	count += *(int *)status;
	free(status);

	printf("The number of prime numbers is %d. \n", count);
}
