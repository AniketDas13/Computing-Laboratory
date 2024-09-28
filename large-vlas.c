/* remember to compile with -std=c23 */
#include "common.h"
#include <locale.h>

static int f(long int n)
{
    int a[n], i;
    FILE *fp;

    if (NULL == (fp = fopen("/dev/null", "w")))
        ERR_MESG("f: error opening file");

    for (i = 0; i < n; i++)
    {
        fprintf(fp, "%d\n", a[i]);
        a[i] = i;
    }

    fclose(fp);

    printf("Function f: done; size of a: %'lu\n", sizeof(a));

    return 0;
}

int main(int ac, char *av[])
{
    int i, j;

    setlocale(LC_NUMERIC, "");
    for (j = 1; j < 7; j++)
    {
        long int n = 1, m;
        for (i = 0; i < j; i++)
            n *= 10;

        long long int a[n];
        printf("n: %'ld, sizeof a: %'lu\n", n, sizeof(a));

        for (i = 0; i < n; i++)
            a[i] = i;

        m = 100;
        printf("%lld %'ld\n", a[1], m);
        f(m);
        m *= 1000;
        printf("%lld %'ld\n", a[2], m);
        f(m);
        m *= 2;
        printf("%lld %'ld\n", a[2], m);
        f(m);
        putchar('\n');
    }

    return 0;
}