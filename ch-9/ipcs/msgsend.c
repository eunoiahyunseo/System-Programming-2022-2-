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

	key = 1234;

	msgqid = msgget(key, IPC_CREAT | 0666);
	printf("msgqid = %d \n", msgqid);
	printf("Enter a string to send: ");
	scanf("%d", &data);
	gets(buf);
	msgsnd(msgqid, buf, strlen(buf) + 1, 0);
}
