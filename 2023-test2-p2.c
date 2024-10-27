#include <stdio.h>

#define NUM_BINS 10

void draw_bar_diagram(int counts[])
{
    int max_height = 0, min_height = 0;

    // Find the maximum and minimum values for the bars
    for (int i = 0; i < NUM_BINS; i++)
    {
        if (counts[i] > max_height)
            max_height = counts[i];
        if (counts[i] < min_height)
            min_height = counts[i];
    }

    // Print the positive part of the bar diagram
    for (int i = max_height; i > 0; i--)
    {
        for (int j = 0; j < NUM_BINS; j++)
        {
            if (counts[j] >= i)
                printf("# ");
            else
                printf("  ");
        }
        printf("\n");
    }

    // Print the X-axis if there are negative values
    if (min_height < 0)
    {
        for (int i = 0; i < NUM_BINS; i++)
            printf("--");
        printf("\n");

        // Print the negative part of the bar diagram
        for (int i = -1; i >= min_height; i--)
        {
            for (int j = 0; j < NUM_BINS; j++)
            {
                if (counts[j] <= i)
                    printf("# ");
                else
                    printf("  ");
            }
            printf("\n");
        }
    }
}

int main()
{
    int counts[NUM_BINS];

    // Read 10 space-separated integers
    for (int i = 0; i < NUM_BINS; i++)
    {
        scanf("%d", &counts[i]);
    }

    draw_bar_diagram(counts);

    return 0;
}