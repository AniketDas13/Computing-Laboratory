#include <stdio.h>
#include <string.h>

int main()
{
    int c;

    while (EOF != (c = fgetc(stdin)))
    {
        int x = (int)c;
        printf("%d ", x);
    }

    return 0;
}