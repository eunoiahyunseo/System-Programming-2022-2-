// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include <sys/types.h>

// #define MAX_BUF 1024
// #define READ 0
// #define WRITE 1

// int main()
// {
// 	pid_t pid;
// 	int fd[2];
// 	char buf[MAX_BUF];

// 	if (pipe(fd) < 0)
// 	{
// 		printf("pipe error\n");
// 		exit(1);
// 	}

// 	if ((pid = fork()) < 0)
// 	{
// 		printf("fork error\n");
// 		exit(1);
// 	}

// 	printf("\n");
// 	if (pid > 0)
// 	{ // parent process
// 		close(fd[READ]);
// 		strcpy(buf, "message from parent\n");
// 		write(fd[WRITE], buf, strlen(buf));
// 	}
// 	else
// 	{ // child process
// 		close(fd[WRITE]);
// 		read(fd[READ], buf, MAX_BUF);
// 		printf("child got message : %s\n", buf);
// 	}
// 	exit(0);
// }

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

typedef struct Data_
{
	int msg_len;
	char msg[100];
} Data;

int main()
{
	int pid, nread, i;
	int fd[2];
	int message_count;
	Data *send_data, *receive_data;
	receive_data = calloc(sizeof(struct Data_), 1);

	pipe(fd);

	pid = fork();

	if (pid == 0) // child
	{
		close(fd[1]);
		nread = read(fd[0], &message_count, sizeof(int));

		for (i = 0; i < message_count; i++)
		{
			memset(receive_data, 0, sizeof(struct Data_));
			nread = read(fd[0], receive_data, sizeof(struct Data_));
			printf("CHILD : %s\n", receive_data->msg);
		}
	}
	else // parent
	{
		close(fd[0]);
		message_count = 2;
		// how many message
		write(fd[1], &message_count, sizeof(int));

		send_data = calloc(sizeof(struct Data_), 1);
		strcpy(send_data->msg, "hello in PA");
		send_data->msg_len = strlen(send_data->msg);
		// printf("sizeof(struct Data_) >> %ld addr >> %p \n", sizeof(struct Data_), send_data);
		write(fd[1], send_data, sizeof(struct Data_));

		send_data = calloc(sizeof(struct Data_), 1);
		strcpy(send_data->msg, "hello in Parent");
		send_data->msg_len = strlen(send_data->msg);
		// printf("sizeof(struct Data_) >> %ld addr >> %p \n", sizeof(struct Data_), send_data);

		write(fd[1], send_data, sizeof(struct Data_));

		wait(NULL);
	}
}