#include <stdio.h>
#include <limits.h> // INT_MAX, INT_MIN

int main()
{
    int N;
    scanf("%d", &N);

    double x, y;
    char color;

    double minRedX = 1e9, maxRedX = -1e9;
    double minRedY = 1e9, maxRedY = -1e9;
    double minBlueX = 1e9, maxBlueX = -1e9;
    double minBlueY = 1e9, maxBlueY = -1e9;

    for (int i = 0; i < N; i++)
    {
        scanf("%lf %lf %c", &x, &y, &color);

        if (color == 'R')
        {
            if (x < minRedX)
                minRedX = x;
            if (x > maxRedX)
                maxRedX = x;
            if (y < minRedY)
                minRedY = y;
            if (y > maxRedY)
                maxRedY = y;
        }
        else
        {
            if (x < minBlueX)
                minBlueX = x;
            if (x > maxBlueX)
                maxBlueX = x;
            if (y < minBlueY)
                minBlueY = y;
            if (y > maxBlueY)
                maxBlueY = y;
        }
    }

    int canSeparateX = (maxRedX < minBlueX || maxBlueX < minRedX);
    int canSeparateY = (maxRedY < minBlueY || maxBlueY < minRedY);

    if (canSeparateX && canSeparateY)
        printf("XY\n");
    else if (canSeparateX)
        printf("X\n");
    else if (canSeparateY)
        printf("Y\n");
    else
        printf("Not possible\n");

    return 0;
}