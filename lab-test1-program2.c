#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main()
{

    int m, n, flag = 0;
    scanf("%d %d", &m, &n);

    long m10 = pow(10, m);
    long n10 = pow(10, n);
    long arr[m10][n10];

    for (int i = 0; i < m10; i++)
    {
        for (int j = 0; j < n10; j++)
        {
            scanf("%ld", &arr[i][j]);
        }
    }

    for (int i = 0; i < m10; i++)
    {
        for (int j = 0; j < n10; j++)
        {
            if (arr[i][j] % n10 == j && arr[i][j] / n10 == i)
            {
                printf("%d %d\n", i, j);
                flag = 1;
            }
        }
    }

    if (flag == 0)
        printf("No treasure found");

    return 0;
}