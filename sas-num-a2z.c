#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isdigit(char c)
{
    if (('0' <= c) && (c <= '9'))
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
    int c;
    char current, next, prev, update = 0;
    int arr[26] = {0};

    while (EOF != (c = fgetc(stdin)))
    {
        if (isdigit(c) == 1)
        {
            continue;
        }
        else if (isalnum(c) == 0)
        {
            continue;
        }
        else
        {
            if (('A' <= c) && (c <= 'Z'))
            {
                arr[c - 'A']++;
            }
            else if (('a' <= c) && (c <= 'z'))
            {
                arr[c - 'a']++;
            }
        }
    }

    for (int i = 0; i < 26; i++)
    {
        printf("\ncharecter %c count: %d", 'a' + i, arr[i]);
    }

    return 0;
}