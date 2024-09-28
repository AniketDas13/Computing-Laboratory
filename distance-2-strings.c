#include "common.h"

static int
my_compare(const char *s1, const char *s2)
{
    int changes = 0, i, l = strlen(s1);

    if (strlen(s2) != l)
        return 1;

    for (i = 0; i < l; ++i)
        if (s1[i] != s2[i])
            changes++;

    if (changes > 2)
        return 1;

    return 0;
}

int main(int ac, char *av[])
{
    char string[2][BUF_LEN];
    int m, i, current = 0, other = 1;

    scanf("%d\n", &m);
    if (NULL == fgets(string[current], BUF_LEN, stdin))
        ERR_MESG("distance-2-strings: error reading input");

    for (i = 1; i < m; ++i)
    {
        if (NULL == fgets(string[other], BUF_LEN, stdin))
            ERR_MESG("distance-2-strings: error reading input");

        if (my_compare(string[current], string[other]))
        {
            printf("NO\n");
            exit(0);
        }

        current = 1 - current;
        other = 1 - other;
    }

    printf("YES\n");

    exit(0);
}