#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main() {
	int fd;
	char buff[100];
	int nread;

	fd = open("fifo1", O_WRONLY);
        printf("fd = %d\n", fd);
	
	printf("Enter a string: ");
	gets(buff);
	nread = write(fd, buff, strlen(buff) + 1);
	
	sleep(2);
	printf("nread = %d\n", nread);
	write(fd, &nread,  sizeof(int));
}
