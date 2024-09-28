#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int x, c1 = 0, c2 = 0;

    while (EOF != (x = fgetc(stdin)))
    {
        if ((x - '0') == 0)
            c1++;
        if ((x - '0') == 1)
            c2++;
    }

    for (int i = 1; i <= c1; i++)
    {
        printf("0");
    }

    for (int i = 1; i <= c2; i++)
    {
        printf("1");
    }

    return 0;
}