#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main()
{
    int flen, glen;
    double f1, f2, a, b;
    double maxfx = -1e9, minfx = 1e9, maxgx = -1e9, mingx = 1e9;

    scanf("%d", &flen);
    double fcodX[flen];
    double fcodY[flen];

    for (int i = 0; i < flen; i++)
    {
        scanf("%lf", &fcodX[i]);
        scanf("%lf", &fcodY[i]);
        if (maxfx < fcodX[i])
            maxfx = fcodX[i];
        if (minfx > fcodX[i])
            minfx = fcodX[i];
    }
    // printf("%lf %lf", minfx, maxfx);

    scanf("%d", &glen);
    double gcodX[glen];
    double gcodY[glen];

    for (int i = 0; i < glen; i++)
    {
        scanf("%lf", &gcodX[i]);
        scanf("%lf", &gcodY[i]);
        if (maxgx < gcodX[i])
            maxgx = gcodX[i];
        if (mingx > gcodX[i])
            mingx = gcodX[i];
    }
    // printf("%lf %lf", mingx, maxgx);

    scanf(" %lf %lf", &f1, &f2);

    if (minfx >= mingx)
        a = minfx;
    else
        a = mingx;

    if (maxfx <= maxgx)
        b = maxfx;
    else
        b = maxgx;

    if (a <= b)
    {
        printf("%lf %lf", a, b);
    }
    else
    {
        printf("None");
    }

    return 0;
}