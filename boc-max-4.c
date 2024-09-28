#include <stdio.h>
int main()
{
    int a, b, c, d, e;
    int max = -1, sum;

    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    while (0 != scanf("%d", &d))
    {
        sum = a + b + c + d;
        max = (sum > max) ? sum : max;
        a = b;
        b = c;
        c = d;
    }

    printf("\nThe maximum is %d", max);

    return 0;
}