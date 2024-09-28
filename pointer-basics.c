#include "common.h"
#include <stdio.h>

int main(int ac, char *av[])
{
    char str0[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char str1[8] = {'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q'};
    char str2[8] = {'z', 'y', 'x', 'w', 'v', 'u', 't', 's'};
    char *cp;

    cp = &str0[0];
    printf("%p %p %c\n", cp, &cp, *cp);
    printf("%p %p %p\n", &str0[0], &str1[0], &str2[0]);
    printf("%p %p %p\n", &str0[7], &str1[7], &str2[7]);

    return 0;
}