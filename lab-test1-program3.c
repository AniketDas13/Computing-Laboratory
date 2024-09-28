#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main()
{

    int m, n, flag = 1;
    scanf("%d %d", &m, &n);

    long m10 = pow(10, m);
    long n10 = pow(10, n);

    long **arr = (long **)malloc(m10 * sizeof(long *));
    for (int i = 0; i < m10; i++)
    {
        arr[i] = (long *)malloc(n10 * sizeof(long *));
    }

    long **temp = (long **)malloc(m10 * sizeof(long *));
    for (int i = 0; i < m10; i++)
    {
        temp[i] = (long *)malloc(n10 * sizeof(long *));
    }
    long val;

    for (int i = 0; i < m10; i++)
    {
        for (int j = 0; j < n10; j++)
        {
            scanf("%ld", &arr[i][j]);
        }
    }

    int i = 0, j = 0;
    printf("(0,0)\n");
    while (flag != 0)
    {
        val = arr[i][j];
        if (arr[i][j] % n10 == j && arr[i][j] / n10 == i)
        {
            printf("Treasure found");
            flag = 0;
            break;
        }
        else if (temp[i][j] == -1)
        {
            printf("Going round in circles");
            flag = 0;
            break;
        }

        temp[i][j] = -1;
        i = val / n10;
        j = val % n10;
        printf("(%d,%d)\n", i, j);
    }

    return 0;
}