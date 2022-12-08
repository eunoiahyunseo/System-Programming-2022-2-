#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>

int main()
{
	int msgqid, nread;
	key_t key;
	char buf[100];
	int data;

	key = 1234;
	msgqid = msgget(key, IPC_CREAT | 0666);
	printf("msgqid = %d \n", msgqid);
	msgrcv(msgqid, buf, 100, 0, 0);
	printf("buf = [%s] \n", buf);
}
