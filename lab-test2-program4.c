#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int m, n, cnt;

void no_pixel(int **R, int i, int j, int **V)
{

    if (R[i][j] == 0)
        return;

    if (V[i][j] != -1)
    {
        V[i][j] = -1;
        cnt++;

        if (i - 1 >= 0 && j - 1 >= 0)
        {
            no_pixel(R, i - 1, j - 1, V);
        }
        if (i - 1 >= 0)
        {
            no_pixel(R, i - 1, j, V);
        }
        if (i - 1 >= 0 && j + 1 < n)
        {
            no_pixel(R, i - 1, j + 1, V);
        }
        if (j - 1 >= 0)
        {
            no_pixel(R, i, j - 1, V);
        }
        if (j + 1 >= 0)
        {
            no_pixel(R, i, j + 1, V);
        }
        if (i + 1 < m && j - 1 >= 0)
        {
            no_pixel(R, i + 1, j - 1, V);
        }
        if (i + 1 < m)
        {
            no_pixel(R, i + 1, j, V);
        }
        if (i + 1 < m && j + 1 < n)
        {
            no_pixel(R, i + 1, j + 1, V);
        }
    }
}

int main()
{
    scanf("%d %d", &m, &n);

    int **R = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        R[i] = (int *)malloc(n * sizeof(int *));
    }

    int **V = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        V[i] = (int *)malloc(n * sizeof(int *));
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            V[i][j] = -2;
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &R[i][j]);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cnt = 0;
            if (R[i][j] == 1 && V[i][j] != -1)
            {
                no_pixel(R, i, j, V);
                printf("%d %d %d\n", j, i, cnt);
            }
        }
    }

    return 0;
}