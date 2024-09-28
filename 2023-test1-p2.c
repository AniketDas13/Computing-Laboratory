#include "common.h"
#include <stdio.h>
#include <time.h>

int main()
{
    int c, counts[10] = {0}, remainder, num_to_remove, n, i, j;

    while ('\n' != (c = getchar()))
    {
        if (isdigit(c))
            counts[c - '0'] += 1;
        else
            fprintf(stderr, "Skipping unexpected character %c\n", c);
    }

    for (i = 0; i < 10; i++)
        remainder += counts[i] * (i % 3);

    remainder %= 3;

    switch (remainder)
    {
    case 0:
        break;

    case 1:
        for (i = 1; i < 10; i += 3)
            if (counts[i] > 0)
            {
                counts[i] -= 1;
                break;
            }

        if (i >= 10)
        {
            num_to_remove = 2;

            for (i = 2; i < 10 && num_to_remove > 0; i += 3)
            {
                if (counts[i] >= num_to_remove)
                {
                    counts[i] -= num_to_remove;
                    num_to_remove = 0;
                }
                else
                {
                    num_to_remove -= counts[i];
                    counts[i] = 0;
                }
            }

            assert(num_to_remove == 0);
        }
        break;

    case 2:
        for (i = 2; i < 10; i += 3)
            if (counts[i] > 0)
            {
                counts[i] -= 1;
                break;
            }

        if (i >= 10)
        {
            num_to_remove = 2;

            for (i = 1; i < 10 && num_to_remove > 0; i += 3)
            {
                if (counts[i] >= num_to_remove)
                {
                    counts[i] -= num_to_remove;
                    num_to_remove = 0;
                }
                else
                {
                    num_to_remove -= counts[i];
                    counts[i] = 0;
                }
            }

            assert(num_to_remove == 0);
        }
        break;
    }

    for (i = 9; i >= 0; i--)
        for (j = 0; j < counts[i]; j++)
            putchar('0' + i);

    putchar('\n');

    return 0;
}