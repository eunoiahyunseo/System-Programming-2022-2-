#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>

int main()
{
	int msgqid, nread;
	key_t key;
	int data;

	key = 1234;
	msgqid = msgget(key, IPC_CREAT | 0666);
	printf("msgqid = %d \n", msgqid);
	msgrcv(msgqid, &data, sizeof(int), 0, 0);

	printf("data = [%d] \n", data);
}
