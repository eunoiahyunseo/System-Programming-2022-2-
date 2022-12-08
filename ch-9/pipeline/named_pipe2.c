#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd;
    char buff[100];

    fd = open("/tmp/fifo1", O_RDWR);
    printf("fd = %d \n", fd);

    read(fd, buff, 100);
    printf("READER : %s \n", buff);
}