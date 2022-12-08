#include <stdio.h>

int main(void)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        sleep(2);
        printf("Hello... \n");
    }

    return 0;
}