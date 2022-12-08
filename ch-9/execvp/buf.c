#include <stdio.h>

int main()
{
    char buf[100];
    while (fgets(buf, 100, stdin) != NULL)
        printf("[hyunseo] %s", buf);
}