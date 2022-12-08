#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main() {
	int fd[2];
	int pid;
	int nread;
	char buff[100];
	pipe(fd);

	printf("fd[0] = %d\n", fd[0]);
	printf("fd[1] = %d\n", fd[1]);

	pid = fork();
	if(pid == 0) { // child process
		close(fd[1]);
		sleep(2);
		nread = read(fd[0], buff, 100);
		printf("CHILD : %s\n", buff);
		printf("nread : %d\n", nread);
		
	} else { // parent process
		close(fd[0]);
		strcpy(buff, "hello");
		write(fd[1], buff, strlen(buff) + 1);
	}
}
