#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd;
    char buff[100];

    fd = open("/tmp/fifo1", O_WRONLY);
    printf("fd = %d \n", fd);
    gets(buff);
    // 해당 파이프에 buff를 쓴다.
    write(fd, buff, strlen(buff) + 1);
}