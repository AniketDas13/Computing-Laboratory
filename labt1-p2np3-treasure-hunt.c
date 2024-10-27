#include "common.h"

#define GET_ROW_NUM(x) ((x) / cols)
#define GET_COL_NUM(x) ((x) % cols)

void list_treasure(unsigned int **A, unsigned int rows, unsigned int cols)
{
    unsigned int i, j, flag = 0;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++) {
            if (GET_ROW_NUM(A[i][j]) == i &&
                GET_COL_NUM(A[i][j]) == j) {
                printf("%d %d\n", i, j);
                flag = 1;
            }
        }
    if (flag == 0) printf("No treasure found.\n");
    return;
}

void treasure_hunt(unsigned int **A, unsigned int rows, unsigned int cols)
{
    unsigned int i = 0, j = 0, next_i, next_j, max = rows*cols;

    while (1) {
        printf("(%d,%d)\n", i, j);
        if (A[i][j] == max) {
            printf("Going round in circles\n");
            return;
        }
        else if (GET_ROW_NUM(A[i][j]) == i && GET_COL_NUM(A[i][j]) == j) {
            printf("Treasure found\n");
            return;
        }
        else {
            next_i = GET_ROW_NUM(A[i][j]);
            next_j = GET_COL_NUM(A[i][j]);
            A[i][j] = max;
            i = next_i, j = next_j;
        }
    }
    return;
}


int main(int ac, char *av[])
{
    unsigned int m, n, rows, cols, i, j;
    unsigned int **A;

    scanf("%d %d", &m, &n);
    for (rows = 1, i = 0; i < m; i++) rows *= 10;
    for (cols = 1, i = 0; i < n; i++) cols *= 10;
    matrix_alloc(A,rows,cols,unsigned int);
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            scanf("%u", &A[i][j]);

    if (ac < 2)
        ERR_MESG("Usage: treasure-hunt <a|b>");
    switch (av[1][0]) {
    case 'a':
        list_treasure(A, rows, cols);
        break;
    case 'b':
        treasure_hunt(A, rows, cols);        
        break;
    default:
        fprintf(stderr, "Unknown option: %c", av[1][0]);
    }
    matrix_free(A);
    return 0;
}
