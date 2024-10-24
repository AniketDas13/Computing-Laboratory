#include "common.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

typedef struct {
  double x, y;
} POINT;

static void print_array(POINT *a, unsigned int n)
{
    printf("%u ", n);
    for (int i=0; i < n; i++)
        printf("%lf %lf ", a[i].x, a[i].y);
    putchar('\n');
    return;
}


int main(int ac, char *av[])
{
    unsigned int m, n, num_xs, i, j;
    double a, b, a0, b0;
    double *all_xs, *f_values, *g_values;
    POINT *f, *g;

    scanf("%u", &m);
    if (NULL == (f = Malloc(m, POINT)))
        ERR_MESG("piecewise-linear: out of memory\n");
    for (i = 0; i < m; i++)
        scanf("%lf %lf", &(f[i].x), &(f[i].y));
    scanf("%u", &n);
    if (NULL == (g = Malloc(n, POINT)))
        ERR_MESG("piecewise-linear: out of memory\n");
    for (i = 0; i < n; i++)
        scanf("%lf %lf", &(g[i].x), &(g[i].y));
    scanf("%lf %lf", &a, &b);
#ifdef DEBUG > 2
    print_array(f, m);
    print_array(g, n);
#endif // DEBUG

    a0 = MAX(f[0].x, g[0].x);
    b0 = MIN(f[m - 1].x, g[n - 1].x);
    if (a0 <= b0)
        printf("%lf %lf\n", a0, b0);
    else
        printf("None\n");
    return 0;
}
