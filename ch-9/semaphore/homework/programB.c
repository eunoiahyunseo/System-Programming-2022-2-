#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	key_t key;
	int shmid;
	char *shmaddr;
	char buf[100];
	memset(buf, 0, 100);
	sem_t *sem1, *sem2;

	sem1 = sem_open("sem1", O_CREAT, 0666, 0);
	sem2 = sem_open("sem2", O_CREAT, 0666, 0);

	// shared memory key
	key = 1004;

	shmid = shmget(key, 100, IPC_CREAT | 0666);

	// get shared memory address
	shmaddr = shmat(shmid, NULL, 0);

	while (1)
	{
		// wait until signal is go up
		sem_wait(sem1);

		if (!strcmp(shmaddr, "end"))
			break;
		else
		{
			printf("RECEIVE FROM PRGRAM_A: %s \n", shmaddr);
			strcat(shmaddr, " hyunseo");
			sem_post(sem2);
		}
	}
	shmdt(shmaddr);
}
