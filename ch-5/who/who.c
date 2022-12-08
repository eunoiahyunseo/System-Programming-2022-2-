#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define SHOWHOST 1

void show_info(struct utmp *, int);
void showtime(const time_t);

int main(void)
{
    struct utmp utbuf;
    int utmpfd;

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
    {
        perror(UTMP_FILE);
        exit(1);
    }

    /* read the struct of utmpd file -> logged in person */
    while (read(utmpfd, &utbuf, sizeof(utbuf)) == sizeof(utbuf))
        show_info(&utbuf, utmpfd);

    close(utmpfd);
    return 0;
}

void showtime(const time_t timeval)
{
    char *cp;
    cp = ctime(&timeval);

    printf(" %12.12s", cp + 4);
}

void show_info(struct utmp *utbufp, int utmpfd)
{
    printf("utmpfd (file descriptor value) >> %d\n", utmpfd);
    // printf("user type >> %d\n", utbufp->ut_type); // expect current user is 7 ( USER_PROCESS )
    // if (utbufp->ut_type != USER_PROCESS) /* users only */
    //     return;d

    printf("%-8.8s ", utbufp->ut_name); /* the login name */

    printf(" %-8.8s ", utbufp->ut_line); /* the tty */

    showtime(utbufp->ut_time); /* displat time */

#ifdef SHOWHOST
    printf(" (%s)", utbufp->ut_host); /* the host */
#endif

    printf("\n");
}