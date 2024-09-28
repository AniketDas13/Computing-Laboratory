#include <stdio.h>
#include <string.h>

int compare(char *a, char *b, int k, int m)
{
    int i;
    for (i = 0; i < m; i++)
    {
        if (a[i + k] != b[i])
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    char a[100];
    char b[50];
    scanf("%s", a);
    scanf("%s", b);

    int len1 = strlen(a);
    int len2 = strlen(b);

    int i, j;
    int count = 0;
    for (i = 0; i <= len1 - len2; i++)
    {
        if (compare(a, b, i, len2) == 1)
        {
            count++;
        }
    }

    printf("The number of occurences of the B string in A string is %d", count);

    return 0;
}