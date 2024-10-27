#include <stdio.h>
#include <stdlib.h>

#define NUM_BINS 10

int calculate_traversal_distance(int counts[])
{
    int distance = 0;

    // Traverse each bar and calculate distance
    for (int i = 0; i < NUM_BINS - 1; i++)
    {
        // Vertical distance (absolute difference in height between adjacent bars)
        distance += abs(counts[i + 1] - counts[i]);
    }

    // Horizontal distance (each bar occupies one unit width)
    distance += NUM_BINS;

    // Add the initial and final vertical segments of the bar chart
    distance += counts[0] + counts[NUM_BINS - 1];

    return distance;
}

int main()
{
    int counts[NUM_BINS];

    // Read 10 space-separated integers
    for (int i = 0; i < NUM_BINS; i++)
    {
        scanf("%d", &counts[i]);
    }

    // Calculate and print traversal distance
    printf("%d\n", calculate_traversal_distance(counts));

    return 0;
}