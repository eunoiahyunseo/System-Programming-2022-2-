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
pthread_mutex_t count_lock;
void *prime_count(void *arg)
{
	int count = 0;
	char checkString[100];
	strcpy(checkString, (char *)arg);

	int start_n;
	if (!strcmp(checkString, "even"))
		start_n = 2;
	else
		start_n = 3;

	for (int i = start_n; i <= n; i += 2)
		if (isPrime(i))
			count++;

	pthread_mutex_lock(&count_lock);
	total_count += count;
	pthread_mutex_unlock(&count_lock);
	printf("Thread is done \n");
}

int main()
{
	int status, count;
	pthread_t thrd1, thrd2;

	printf("Enter a positive integer : ");
	scanf("%d", &n);

	char checkString[100] = {0};

	// function argument is void* -> char* form
	strcpy(checkString, "even");
	pthread_create(&thrd1, NULL, prime_count, checkString);
	strcpy(checkString, "odd");
	pthread_create(&thrd2, NULL, prime_count, checkString);

	pthread_join(thrd1, &status);
	pthread_join(thrd2, &status);

	printf("The number of prime number is %d. \n", total_count);
}
