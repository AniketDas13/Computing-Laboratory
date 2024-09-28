#include <stdio.h>

int stlen(char *s)
{
    int length = 0;
    int i = 0;

    while (s[i] != '\0')
    {
        i++;
        length++;
    }

    return length;
}

int strcmp(char *s, char *t)
{
    int count = 0;

    while (*s == *t)
    {
        count = 1;
        s++;
        t++;
    }

    return count;
}

int diffByOne(char *s, char *t)
{
    int diff;

    if (stlen(s) != stlen(t))
    {
        return 0;
    }
    else
    {
        int i = 0;
        int len = stlen(s);
        diff = 0;

        for (i = 0; i < len; i++)
        {
            if (s[i] != t[i])
            {
                diff++;
            }
        }
    }

    if (diff == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    char a[100];
    char b[100];

    scanf("%s", a);
    scanf("%s", b);
    printf("Result of strlen is %d and %d", stlen(a), stlen(b));
    printf("\nResult of strcmp is %d", strcmp(a, b));
    printf("\nThe result of diffbyone is %d", diffByOne(a, b));

    return 0;
}