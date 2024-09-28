#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int c;
    char current, next, prev, update = 0;

    while (EOF != (c = fgetc(stdin)))
    {
        if (isalnum(c) == 0)
        {
            continue;
        }

        if (('a' <= c) && (c <= 'z'))
        {
            current = c;
            update = 1;
        }
        else if (('0' <= c) && (c <= '9'))
        {
            int num = c - '0';
            int i = 0;
            for (i = 0; i < num - 1; i++)
            {
                printf("%c", current);
            }
            update = 0;
        }

        if (update == 1)
        {
            printf("%c", current);
        }
    }

    return 0;
}