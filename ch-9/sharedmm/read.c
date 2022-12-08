#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

int main(void)
{
	int shmid;
	char buf[100];
	char *shmaddr;
	key_t key;
	key = 1234;

	// share 1024 byte memory
	shmid = shmget(key, 1024, IPC_CREAT | 0666);
	printf("shmid = %d \n", shmid);

	// get shared memory address
	shmaddr = shmat(shmid, NULL, 0);
	printf("shmaddr = %p \n", shmaddr);
	strcpy(buf, shmaddr);
	printf("buf = [%s] \n", shmaddr);
	shmdt(shmaddr);
}
