#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main()
{
	key_t key;
	int shmid, i, j;
	void *shmaddr;

	key = 1000;
	shmid = shmget(key, sizeof(int), IPC_CREAT | 0644);
	shmaddr = shmat(shmid, NULL, 0);
	for (i = 0; i < 10; i++)
	{
		// micro sleep
		usleep(200000);
		for (j = 0; j < 10000000; j++)
			(*(int *)shmaddr)++;
	}

	printf("*(int *)shmaddr value = %d \n", *((int *)shmaddr));
	shmdt(shmaddr);
}
