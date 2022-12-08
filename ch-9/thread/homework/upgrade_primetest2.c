#include <stdio.h>
#include <pthread.h>
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
pthread_mutex_t num_lock, count_lock;
int testNum = 2;

void *prime_count(void *arg)
{
	testNum++;
	int count = 0;
	int num;

	while (testNum <= n)
	{
		pthread_mutex_lock(&num_lock);
		num = testNum;
		testNum++;
		pthread_mutex_unlock(&num_lock);

		if (isPrime(num))
		{
			pthread_mutex_lock(&count_lock);
			total_count++;
			pthread_mutex_unlock(&count_lock);
		}
	}

	printf("Thread is done \n");
}

int main()
{
	int status;
	int count;
	pthread_t thrd1, thrd2;

	printf("Enter a positive integer : ");
	scanf("%d", &n);

	// function argument is void* -> char* form
	pthread_create(&thrd1, NULL, prime_count, NULL);
	pthread_create(&thrd2, NULL, prime_count, NULL);

	pthread_join(thrd1, &status);
	pthread_join(thrd2, &status);
	printf("The number of prime number is %d. \n", total_count);
	// work distribution is unfair
}
