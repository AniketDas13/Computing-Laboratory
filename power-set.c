#include <stdio.h>
#include <math.h>

void printPowerSet(int *set, int set_size)
{
    unsigned int pow_set_size = pow(2, set_size);
    int counter, j;

    for (counter = 0; counter < pow_set_size; counter++)
    {
        for (j = 0; j < set_size; j++)
        {
            if (counter & (1 << j))
            {
                // printf("%d & %d => ", counter, (1 << j));
                printf("%d ", set[j]);
            }
        }
        printf("\n");
    }
}

int main()
{
    int set[] = {10, 20, 30};
    int set_size = sizeof(set) / sizeof(set[0]);

    printf("Power set of the given set:\n");
    printPowerSet(set, set_size);

    return 0;
}