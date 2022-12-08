#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

int main(void) {
	int shmid;
	int data;
	void *shmaddr;
	key_t key;
	key = 1225;

	// share 4 byte memory
	shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);	
	printf("shmid = %d \n", shmid);
	
	// get shared memory address
	shmaddr = shmat(shmid, NULL, 0);
	printf("shmaddr = %p \n", shmaddr);

	data = *((int *)shmaddr);
	printf("data = %d \n", data);

	shmdt(shmaddr);
}
