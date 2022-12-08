#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define DELAY 2

// new process takes a nap and then exits
void child_code(int delay) {
    printf("child %d here. will sleep for %d seconds \n", getpid(), delay);
    sleep(delay);
    printf("child done. about to exit \n");
    exit(17);
}

// parent waits for child then prints a message
void parent_code(int childpid) {
    int wait_rv; // return value from wait()
    int child_status;
    int high_8, low_7, bit_7;

    // receive child's status
    wait_rv = wait(&child_status);

    printf("done waiting for %d. Wait returned: %d \n", childpid, wait_rv);

    /* 1111 1111 0000 0000 */
    high_8 = child_status >> 8; // exit

    /* 0000 0000 0111 1111 */
    low_7 = child_status & 0x7f; // signal number

    /* 0000 0000 1000 0000 */
    bit_7 = child_status & 0x80; // core dump flag
    printf("status: exit=%d, sig=%d, core=%d \n", high_8, low_7, bit_7);
}

int main(int argc, char *argv[]) {
    int newpid;
    void child_code(), parent_code();

    printf("before: mypid is %d \n", getpid());
    
    if((newpid = fork()) == -1) {
        perror("fork");
    } else if(newpid == 0) { // child process
        child_code(DELAY);
    } else { // parent process
        parent_code(newpid);
    }
}