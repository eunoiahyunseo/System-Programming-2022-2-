/**
 *	semaphore : 정수변수
 *
 *	------------< semaphore의 값을 바꿀 수 있는 함수들 >------------
 *	signal() -> s++;
 *	-> atomic하게 실행된다.
 *
 *
 *	wait() -> while(s<=0) block; s--;
 *	-> aotmic하게 실행된다.
 *
 *	---- 모든 프로세스가 signal(), wait()를 한 시점에 한 프로세스만 실행될 수 있게 보장을 한다. ----
 *
 *
 *	init() -> 단 한번만, 초깃값을 지정해 줄 수 있다.
 */

#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
	sem_t *sem; // semaphore data type -> sem_t
	int svalue;
	int ival;

	printf("Enter the initial value : ");
	scanf("%d", &ival);
	sem = sem_open("testsem", O_CREAT, 0666, ival); // value 1 is a init value in semaphore
	sem_getvalue(sem, &svalue);
	printf("svalue = %d \n", svalue);
	printf("sem = %p\n", sem);
}
