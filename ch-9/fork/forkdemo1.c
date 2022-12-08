// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>

// int main(int argc, char *argv[])
// {
//     int ret_from_fork, mypid;

//     mypid = getpid();
//     printf("Before: my pid is %d\n", mypid);
//     ret_from_fork = fork();
//     sleep(1);

//     printf("After: my pid is %d, fork() said %d\n", getpid(), ret_from_fork);
// }

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = getpid();
    int result;

    printf("Hello. my pid = %d\n", pid);
    result = fork();
    
    pid = getpid();
    printf("After fork, Hello again. my pid = %d\n", pid);
}