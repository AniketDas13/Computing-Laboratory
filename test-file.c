#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int a = 10;
    int b = 20;

    // Seed the random number generator
    // Otherwise same sequence of random number is produced on every run
    srand(time(NULL));

    for (int i = 0; i < 5; i++)
    {
        int random_number = rand();
        int result = a + random_number % (b - a + 1);
        printf("Random number between %d and %d: %d\n", a, b, result);
    }

    return 0;
}