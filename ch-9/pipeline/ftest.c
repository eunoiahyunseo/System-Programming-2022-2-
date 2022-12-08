#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int pid, fd;
    char child_buf[100] = {"hello in child \n"};
    char parent_buf[100] = {"hello in parent \n"};

    fd = open("test.txt", O_RDWR | O_CREAT, 0666);
    printf("fd = %d \n", fd);

    pid = fork();
    if (pid == 0)
    { // child process
        sleep(2);
        write(fd, child_buf, strlen(child_buf) + 1);
    }
    else
    { // parent process
        sleep(1);
        write(fd, parent_buf, strlen(parent_buf) + 1);
    }
}