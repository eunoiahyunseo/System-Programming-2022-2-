#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    int msgqid;
    key_t key;
    int data;

    key = 1234;

    msgqid = msgget(key, IPC_CREAT | 0666);
    printf("msgqid = %d \n", msgqid);
    printf("Enter a string to send: ");
    scanf("%d", &data);

    msgsnd(msgqid, &data, sizeof(int), 0);
    data++;
    msgsnd(msgqid, &data, sizeof(int), 0);
}
