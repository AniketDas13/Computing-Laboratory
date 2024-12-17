#include <stdio.h>
#include <stdlib.h>

int main()
{
    int seed = 42;

    printf("Random numbers without srand:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", rand() % 100);
    }
    printf("\n");

    printf("Random numbers with srand(seed=42):\n");
    srand(seed); // Seed the random number generator
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", rand() % 100);
    }
    printf("\n");

    printf("Resetting srand(seed=42):\n");
    srand(seed); // Re-seeding with the same value
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", rand() % 100);
    }
    printf("\n");

    return 0;
}