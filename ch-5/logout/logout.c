#include <stdio.h>
#include <utmp.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int logout_tty(char *line)
{
    int fd;
    struct utmp rec;
    int len = sizeof(struct utmp);
    int retval = -1; /* pessimism */

    /* when open cannot open a file, it returns -1. */
    if ((fd = open(UTMP_FILE, O_RDWR)) == -1) /* open file */
        return -1;

    /* search and replace */
    /* when read cannot read data, it returns -1. */
    while (read(fd, &rec, len) == len)
    {
        if (!strncmp(rec.ut_line, line, sizeof(rec.ut_line)))
        {
            rec.ut_type = DEAD_PROCESS;
            if (time(&rec.ut_time) != -1)
            {
                /* when lseek cannot seek, it returns -1. */
                if (lseek(fd, -len, SEEK_CUR) != -1)
                {
                    if (write(fd, &rec, len) == len)
                    {
                        retval = 0;
                    }
                }
            }
            break;
        }
    }

    /* close the file */
    if (close(fd) == -1)
        retval = -1;

    return retval;
}