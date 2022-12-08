#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fork_rv, sum, wait_ret;
    printf("Before: my pid is %d\n", getpid());
    sum = 1;
        
    fork_rv = fork();

    if (fork_rv == 1) // error with fork
        perror("fork");
    else if (fork_rv == 0) { // child process
        sleep(5);
        sum += 10;
        printf("sum in child process (%d)= %d addr = %p \n", getpid(), sum, &sum);
    }
    else { // parent process
        wait_ret = wait(NULL); // wait until child process is done
        sum += 20;
        printf("sun in parent process = %d addr = %p \n", sum, &sum);
        printf("wait return value = %d \n", wait_ret);
    }
}