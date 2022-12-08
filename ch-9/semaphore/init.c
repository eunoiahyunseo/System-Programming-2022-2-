#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main() {
	key_t key;
	int shmid;
	int *shmaddr;
	
	key = 1000;
	shmid = shmget(key, sizeof(int), IPC_CREAT | 0644);
	shmaddr = shmat(shmid, 0, 0);
	*shmaddr = 0;
	shmdt(shmaddr);
}
