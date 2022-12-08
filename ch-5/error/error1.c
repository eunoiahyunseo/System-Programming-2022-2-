#include <errno.h>
#include <fcntl.h>

#define DEFAULT_MODE 0644
int sample(char *filename)
{
    int fd;
    fd = open(filename, O_RDONLY, DEFAULT_MODE);
    if (fd == -1)
    {
        // printf("Cannot open file: ");
        // if (errno == ENOENT)
        //     printf("There is no such file\n");
        // else if (errno == EINTR)
        //     printf("Interrupted while opening file.");
        // else if (errno == EACCES)
        //     printf("You do not have permission to open file.");
        perror("Cannot open file.");
        return;
    }
}

int main(int argc, char *argv[])
{
    char input_filename[100] = {0};
    scanf("%s", input_filename);
    sample(input_filename);

    return 0;
}