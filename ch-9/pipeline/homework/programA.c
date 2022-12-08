/**
 * program A
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int fd1, fd2;
	fd1 = open("../fifo1", O_WRONLY);
	fd2 = open("../fifo2", O_RDONLY);

	char buff[100];

	while (1)
	{
		printf("문자열을 입력해주세요: ");
		gets(buff);
		if (!strcmp(buff, "end"))
			break;
		else
		{
			write(fd1, buff, strlen(buff) + 1);
			read(fd2, buff, 100);
			printf("READER CONCAT : %s\n", buff);
			memset(buff, 0, 100);
		}
	}
}
