/* write0.c
        Purpose: send messages to another terminal
        Method: open the other terminal for output then
                copy from stdin to that terminal
        shows: a terminal is just a file supporting regular I/O
        Usage: write0 ttyname
        Writer: hyunseo in knu.
*/

#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    int fd;
    char buf[BUFSIZ]; /* BUFSIZ: 8192 depending on system */

    /* check args */
    if (argc != 2)
    {
        fprintf(stderr, "usage: write0 ttyname\n");
        exit(1);
    }

    /* open devices */
    if ((fd = open(argv[1], O_WRONLY)) == -1)
    {
        perror(argv[1]);
        exit(1);
    }

    /* loop until EOF on input */
    while (fgets(buf, BUFSIZ, stdin) != NULL)
        if (write(fd, buf, strlen(buf)) == -1)
            break;

    close(fd);

    return 0;
}
