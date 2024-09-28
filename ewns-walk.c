#include "common.h"
#include <math.h>
#include <stdio.h>

int main(int ac, char *av[])
{
    int c, v = 0, h = 0;

    while (1)
    {
        c = getchar();
        switch (c)
        {
        case 'E':
            h++;
            break;
        case 'W':
            h--;
            break;
        case 'N':
            v++;
            break;
        case 'S':
            v--;
            break;
        default: /* end of string; do the actual processing here */
            printf("%f\n", sqrt(h * h + v * v));
            exit(0);
        }
    }

    return 0;
}