#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = getpid();
    int result;

    printf("Hello. my pid = %d \n", pid);
    result = fork();
    
    
    pid = getpid();
    printf("After fork, my pid = %d, result = %d \n", pid, result);

}