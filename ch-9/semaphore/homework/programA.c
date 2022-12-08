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
	sem_t *sem1, *sem2;
	char buf[100];
	memset(buf, 0, 100);

	sem1 = sem_open("sem1", O_CREAT, 0666, 0);
	sem2 = sem_open("sem2", O_CREAT, 0666, 0);

	// shared memory key
	key = 1004;

	shmid = shmget(key, 100, IPC_CREAT | 0666);

	// get shared memory address
	shmaddr = shmat(shmid, NULL, 0);
	memset(shmaddr, 0, 100);

	while (1)
	{
		memset(shmaddr, 0, 100);
		// put shm to message
		printf("WRITE TO PROGRAM_B: ");
		gets(buf);
		if (!strcmp(buf, "end"))
		{
			strcpy(shmaddr, buf);
			sem_post(sem1);
			break;
		}
		else
		{
			// write to shared memory
			strcpy(shmaddr, buf);
			sem_post(sem1);

			sem_wait(sem2);
			printf("CONCAT_STRING: %s \n", shmaddr);
		}
	}
	shmdt(shmaddr);
}
