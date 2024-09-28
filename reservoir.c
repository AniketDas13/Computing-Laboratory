#include "common.h"
#include <stdio.h>

#define MAX_MINUTES 1000

int main(int ac, char *av[])
{
    int T, D, i;
    double f, X = 0, Y = 0;

    scanf("%d %d", &T, &D);
    for (i = 0; i < T; ++i)
    {
        if (1 != scanf("%lf", &f))
            ERR_MESG("reservoir: error reading tap");
        X += 1.0 / f;
    }
    for (i = 0; i < D; ++i)
    {
        if (1 != scanf("%lf", &f))
            ERR_MESG("reservoir: error reading drain");
        Y += 1.0 / f;
    }
    if (X == Y)
        printf("(A)\n(C)\n");
    else if (X > Y)
        printf("(B) %.2f\n(C)\n", 1 / (X - Y));
    else
        printf("(A)\n(D) %.2f\n", 1 / (Y - X));

    return 0;
}