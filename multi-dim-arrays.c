#include <stdio.h>

#define ROWS 2
#define COLS 3

// Compiler version gcc  6.3.0

void print_matrixA(int **matrix)
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
}

void print_matrixB(int (*matrix)[COLS])
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
}

void print_matrixC(int matrix[ROWS][COLS])
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
}

void print_matrixD(int **matrix)
{
    int i, *base = (int *)matrix;
    for (i = 0; i < ROWS * COLS; i++)
    {
        if (i % COLS == 0)
            putchar('\n');
        printf("%d ", base[i]);
    }
}

int main()
{
    /* IMPORTANT NOTE about initialisation: */
    int a[ROWS][COLS] = {0};
    int i, j, *p, **pp;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            a[i][j] = i * COLS + j;
    pp = a;
    printf("%p %lu\n", pp, pp);

    p = (int *)a;
    printf("Start: %p %lu\nEnd: %p %lu\n",
           p, p, p + ROWS * COLS, p + ROWS * COLS);

    p += ROWS;
    printf("%d\n", *p);
    p += (COLS - ROWS);
    printf("%d\n", *p);
    p = (int *)a + ROWS * COLS - 1;
    printf("%d\n", *p);

    puts("With print_matrixB:");
    print_matrixB(a);
    print_matrixB(pp);

    puts("With print_matrixC:");
    print_matrixC(a);
    print_matrixC(pp);

    printf("With print_matrixD:");
    print_matrixD(a);
    print_matrixD(pp);

    puts("\nWith print_matrixA:");
    print_matrixA(a);
    print_matrixA(pp);

    return 0;
}