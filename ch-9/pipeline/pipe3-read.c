#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main() {
	int fd;
	char buff[100];
	int nread, data;

	fd = open("fifo1", O_RDWR);
        printf("fd = %d\n", fd);

	nread = read(fd, buff, 100);
	printf("READER : %s \n", buff);
	
	nread = read(fd, &data, sizeof(int));
	printf("READER data = %d\n", data);
}
