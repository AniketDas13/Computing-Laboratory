#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct NODE
{
    int col;
    float marks;
};

struct MOV
{
    int col;
    int total;
};

// int compare(const void *a, const void *b)
// {
//     const struct NODE *pa = (const struct NODE *)a;
//     const struct NODE *pb = (const struct NODE *)b;
//     return (pa->marks - pb->marks);
// }

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
            nodes[j].marks = (float)R[i][j];
        }

        // qsort(nodes, n, sizeof(nodes[0]), compare);
        for (int j = 0; j < n - 1; j++)
            for (int k = 0; k < n - j - 1; k++)
                if (nodes[k].marks < nodes[k + 1].marks)
                {
                    struct NODE temp = nodes[k];
                    nodes[k] = nodes[k + 1];
                    nodes[k + 1] = temp;
                }

        for (int j = 0; j < n; j++)
        {
            RES[i][nodes[j].col] = j + 1;
        }
    }

    struct MOV *movs = (struct MOV *)malloc(n * sizeof(struct MOV *));
    for (int j = 0; j < n; j++)
    {
        int sum = 0;
        for (int i = 0; i < m; i++)
        {
            sum += RES[i][j];
        }
        movs[j].col = j;
        movs[j].total = sum;
    }

    for (int j = 0; j < n - 1; j++)
        for (int k = 0; k < n - j - 1; k++)
            if (movs[k].total > movs[k + 1].total)
            {
                struct MOV temp = movs[k];
                movs[k] = movs[k + 1];
                movs[k + 1] = temp;
            }

    float rank[n];
    for (int j = 0; j < n; j++)
    {
        rank[movs[j].col] = j + 1;
        int k = j;
        float cnt = 1.0;
        float sum = rank[movs[j].col];
        while (movs[k].total == movs[k - 1].total)
        {
            sum += rank[movs[j - 1].col];
            cnt++;
            k--;
        }
        float temp = sum / (float)cnt;
        while (k <= j)
        {
            rank[movs[k].col] = temp;
            k++;
        }
    }

    for (int j = 0; j < n; j++)
    {
        printf("%.1f ", rank[j]);
    }

    return 0;
}