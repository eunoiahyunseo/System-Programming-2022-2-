#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
	sem_t *sem; // semaphore data type -> sem_t

	// 프로세스 간의 semaphore는 이름이 필요하지만, 프로세스 안에 쓰레드간의 통신은 semaphore 이름이 필요없다.
	sem = sem_open("testsem", O_CREAT, 0666, 0);
	printf("sem = %p\n", sem);

	// wait
	sem_wait(sem);
	printf("Testing...\n");
	sleep(10);

	// signal
	sem_post(sem);
}
