#include <stdio.h>
#include <pthread.h>

int isPrime(int n)
{
	for (int i = 2; i <= n / 2; i++)
		if (n % i == 0)
			return 0;

	return 1;
}

int n;
struct PrimeTestRange
{
	int startN;
	int endN;
};
int total_count = 0;
pthread_mutex_t count_lock;

void *prime_count(void *arg)
{
	int count = 0;
	struct PrimeTestRange range;
	range = *(struct PrimeTestRange *)arg;

	for (int i = range.startN; i <= range.endN; i++)
		if (isPrime(i))
		{
			/**
			 *	말 그대로 열쇠를 가지고 가는 것이라고 생각하면 됨
			 *	열쇠를 반환해야 다른 사람이 이제 따고 사용할 수 있는 원리인 것이다.
			 */
			// 이것의 사용 범위가 넓어지면 병렬화의 효과가 없어질 수도 있다.
			count++;
		}

	pthread_mutex_lock(&count_lock);
	total_count += count;
	pthread_mutex_unlock(&count_lock);
	printf("Thread is done \n");
}

int main()
{
	int status;
	int count;
	struct PrimeTestRange r1, r2;
	pthread_t thrd1, thrd2;

	printf("Enter a positive integer : ");
	scanf("%d", &n);

	r1.startN = 2;
	r1.endN = n / 2;

	r2.startN = n / 2 + 1;
	r2.endN = n;

	// function argument is void* form
	pthread_create(&thrd1, NULL, prime_count, &r1);
	pthread_create(&thrd2, NULL, prime_count, &r2);

	pthread_join(thrd1, &status);
	pthread_join(thrd2, &status);
	printf("The number of prime number is %d. \n", total_count);
	// work distribution is unfair
}
