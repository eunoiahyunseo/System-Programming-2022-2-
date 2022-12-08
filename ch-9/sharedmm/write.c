#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

int main()
{
	key_t key;
	key = 1234;
	int shmid;

	char *shmaddr;
	char buf[100];

	// allocate shared memory -> 1024 byte (=malloc)
	shmid = shmget(key, 1024, IPC_CREAT | 0666);
	printf("shmid = %d \n", shmid);

	shmaddr = shmat(shmid, NULL, 0);

	printf("Enter a string : ");
	gets(buf);

	strcpy(shmaddr, buf);

	// typeof free some memory
	shmdt(shmaddr);
}