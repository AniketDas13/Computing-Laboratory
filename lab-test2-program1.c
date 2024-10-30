#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct NODE
{
    int col;
    double marks;
};

int compare(const void *a, const void *b)
{
    const struct NODE *pa = (const struct NODE *)a;
    const struct NODE *pb = (const struct NODE *)b;
    if (pa->marks > pb->marks)
    {
        return -1;
    }
    else if (pa->marks < pb->marks)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{

    int m, n;
    scanf("%d %d", &m, &n);

    double **R = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++)
    {
        R[i] = (double *)malloc(n * sizeof(double *));
    }

    long **RES = (long **)malloc(m * sizeof(long *));
    for (int i = 0; i < m; i++)
    {
        RES[i] = (long *)malloc(n * sizeof(long *));
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &R[i][j]);
        }
    }

    for (int i = 0; i < m; i++)
    {
        struct NODE *nodes = (struct NODE *)malloc(n * sizeof(struct NODE *));

        for (int j = 0; j < n; j++)
        {
            nodes[j].col = j;
            nodes[j].marks = (double)R[i][j];
        }

        qsort(nodes, n, sizeof(nodes[0]), compare);
        // for (int j = 0; j < n - 1; j++)
        //     for (int k = 0; k < n - j - 1; k++)
        //         if (nodes[k].marks < nodes[k + 1].marks)
        //         {
        //             struct NODE temp = nodes[k];
        //             nodes[k] = nodes[k + 1];
        //             nodes[k + 1] = temp;
        //         }

        for (int j = 0; j < n; j++)
        {
            RES[i][nodes[j].col] = j + 1;
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%ld ", RES[i][j]);
        }
        printf("\n");
    }

    return 0;
}