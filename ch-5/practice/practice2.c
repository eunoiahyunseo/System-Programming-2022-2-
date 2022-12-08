#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int a, b;
    a = 0;
    b = 0x0;
    fd = open("practice1.data", O_RDONLY);
    read(fd, &a, sizeof(int));
    read(fd, &b, sizeof(int));
    printf("a = %d, b = %x \n", a, b);
    close(fd);
}