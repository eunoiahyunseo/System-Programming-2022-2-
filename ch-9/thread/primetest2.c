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

void *prime_count(void *arg)
{
	int count = 0;
	struct PrimeTestRange range;
	range = *(struct PrimeTestRange *)arg;

	for (int i = range.startN; i <= range.endN; i++)
		if (isPrime(i))
			count++;
	printf("thrd count = %d \n", count);
	total_count += count;
	// pthread_exit parameter is void*
	// pthread_exit(count);
	/**
	 * pthread_exit(&count);
	 * -> 지역변수의 주소이기 때문에 쓸모가 없어진다.
	 */
	// *ptr = count;
	// heap공간은 남아있기 때문에 사용할 수 있다.
	// 그래서 struct도 반환값으로 넘겨줄 수도 있다.
	// pthread_exit(ptr);
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
}
