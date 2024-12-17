#include <stdio.h>
#include <stdlib.h>
#include "map-filter.c"

void square(void *input, void *output)
{
    int *in = (int *)input;
    int *out = (int *)output;
    *out = (*in) * (*in);
}

int isEven(void *input)
{
    int *value = (int *)input;
    return (*value % 2 == 0);
}

int main()
{
    int L[] = {-1, 3, -8, 7, 2, 5, 6};
    unsigned int N = sizeof(L) / sizeof(L[0]);

    printf("Original list L: ");
    for (unsigned int i = 0; i < N; i++)
    {
        printf("%d ", L[i]);
    }
    printf("\n");

    int *squared = (int *)map(L, N, sizeof(int), sizeof(int), square);

    printf("Mapped list R: ");
    for (unsigned int i = 0; i < N; i++)
    {
        printf("%d ", squared[i]);
    }
    printf("\n");

    int even_cnt = filter(L, N, sizeof(int), isEven);

    printf("Filtered list L: ");
    for (unsigned int i = 0; i < N; i++)
    {
        printf("%d ", L[i]);
    }
    printf("\nNumber of elements: %d\n", even_cnt);

    return 0;
}