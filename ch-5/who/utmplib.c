// utmplib.c - functions to buffer reads from utmp file
/**
 * utmplib.c contains the dbuffer and variables and functions
 * to manage data flow through the buffer
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utmp.h>
#include <time.h>

#define SHOWHOST 1

void show_info(struct utmp *);
void showtime(const time_t);

/**
 * the variables num_recs and cur_rec record how many structures
 * are in the buffer and how many have been used
 */

#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NRECS * UTSIZE]; /* storage */
static int num_recs;                 /* num stored */
static int cur_rec;                  /* next to go */
static int fd_utmp = -1;             /* read from */

/** declare the flowing functions to be written below. */
int utmp_reload();
int utmp_open(char *);
struct utmp *utmp_next();
void utmp_close();

int main()
{
    struct utmp *utbufp;      /* holds pointer to next rec */
    struct utmp *utmp_next(); /* returns pointer to next */

    /* open the UTMP file */
    if (utmp_open(UTMP_FILE) == -1)
    {
        perror(UTMP_FILE);
        exit(1);
    }

    /* start to read an UTMP record from the UTMP file */
    while ((utbufp = utmp_next()) != NULLUT)
        show_info(utbufp);

    utmp_close();
    return 0; /* close the opened UTMP file */
}

/*
    Open the UTMP file
    return: a file descriptor of the file
*/

int utmp_open(char *filename)
{
    fd_utmp = open(filename, O_RDONLY); /* oepn it */
    cur_rec = num_recs = 0;             /* no recs yet */
    return fd_utmp;
}

/*
    Access the next UTMP record if any
    return: the pointer of the next record
*/

struct utmp *utmp_next()
{
    struct utmp *recp;
    if (fd_utmp == -1) /* error? */
        return NULLUT;

    if ((cur_rec == num_recs) && utmp_reload() == 0)
        return NULLUT;

    recp = (struct utmp *)&utmpbuf[cur_rec * UTSIZE];
    cur_rec++;
    return recp;
}

/*
    Read next bunch of records into buffer
    return: how many bytes read
*/

int utmp_reload()
{
    int amt_read;
    amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
    /* num_recs -> fd_utmp's utmp struct number */
    num_recs = amt_read / UTSIZE;
    cur_rec = 0;
    return num_recs;
}

void utmp_close()
{
    if (fd_utmp != -1) /* don't close if still not open */
        close(fd_utmp);
}

void showtime(const time_t timeval)
{
    char *cp;
    cp = ctime(&timeval);

    printf(" %12.12s", cp + 4);
}

void show_info(struct utmp *utbufp)
{
    // printf("user type >> %d\n", utbufp->ut_type); // expect current user is 7 ( USER_PROCESS )
    if (utbufp->ut_type != USER_PROCESS) /* users only */
        return;

    printf("%-8.8s ", utbufp->ut_name); /* the login name */

    printf(" %-8.8s ", utbufp->ut_line); /* the tty */

    showtime(utbufp->ut_time); /* displat time */

#ifdef SHOWHOST
    printf(" (%s)", utbufp->ut_host); /* the host */
#endif

    printf("\n");
}