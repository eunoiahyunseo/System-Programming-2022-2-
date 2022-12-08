/**
 * program B
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int fd1, fd2;
	fd1 = open("../fifo1", O_RDONLY);
	fd2 = open("../fifo2", O_WRONLY);

	char buff[100];

	while (1)
	{
		read(fd1, buff, 100);
		printf("READER : %s \n", buff);
		strcat(buff, " hyunseo");
		write(fd2, buff, strlen(buff) + 1);
		memset(buff, 0, 100);
	}
}
