#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_MAXSIZE 100

int main(void) {
	int msgqid1, msgqid2;
	key_t key1, key2;
	key1 = 1000, key2 = 1001;
	msgqid1 = msgget(key1, IPC_CREAT | 0666);	
	msgqid2 = msgget(key2, IPC_CREAT | 0666);
	char buf[BUFFER_MAXSIZE];

	while(1) {
		msgrcv(msgqid1, buf, BUFFER_MAXSIZE, 0, 0);
		if(!strcmp(buf, "end")) break;

		printf("READER : %s \n", buf);
		
		strcat(buf, " hyunseo");
		msgsnd(msgqid2, buf, strlen(buf) + 1, 0);
		memset(buf, 0, BUFFER_MAXSIZE);
	}
}
