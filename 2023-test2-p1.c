#include <stdio.h>

int main()
{
    int histogram[10] = {0}; // Initialize histogram bins
    int num;

    // Read integers from stdin until end-of-input
    while (scanf("%d", &num) != EOF)
    {
        if (num >= 1 && num < 1000)
        {
            int bin = num / 100; // Directly calculate the bin without subtracting 1
            histogram[bin]++;
        }
    }

    // Output the histogram as space-separated values
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", histogram[i]);
    }
    printf("\n");

    return 0;
}