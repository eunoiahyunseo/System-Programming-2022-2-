#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    int a, b;
    a = -100;
    b = 0x12345678;
    fd = open("practice1.data", O_WRONLY | O_CREAT);
    write(fd, &a, sizeof(int));
    write(fd, &b, sizeof(int));
    printf("%d", a);
    close(fd);
}