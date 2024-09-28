#include "common.h"
#include <stdio.h>
#include <math.h>
#include <time.h>

#define MY_RAND_MAX 10000

static double entropy(int min, int max)
{
    double total, prob_smaller, prob_larger;

    if (min == 0)
        return 0;

    total = min + max;
    prob_smaller = min / total;
    prob_larger = max / total;

    return -(prob_smaller * log2(prob_smaller) + prob_larger * log2(prob_larger));
}

int main()
{
    int c, count0 = 0, count1 = 0, count_noisy = 0, max, min;
    double min_entropy, max_entropy;

    while ('\n' != (c = getchar()))
    {
        switch (c)
        {
        case '0':
            count0++;
            break;
        case '1':
            count1++;
            break;
        case '?':
            count_noisy++;
            break;
        default:
            fprintf(stderr, "Skipping unexpected character %c\n", c);
            break;
        }
    }

    if (count0 > count1)
    {
        max = count0;
        min = count1;
    }
    else
    {
        max = count1;
        min = count0;
    }

    if (count_noisy == 0)
    {
        min_entropy = max_entropy = entropy(min, max);
    }
    else
    {
        min_entropy = entropy(min, max + count_noisy);

        if (count_noisy < max - min)
            max_entropy = entropy(min + count_noisy, max);
        else
            max_entropy = 1;
    }

    printf("%.3f %.3f\n", min_entropy, max_entropy);

    return 0;
}