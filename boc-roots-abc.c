#include <stdio.h>
#include <math.h>
int main()
{
    float a, b, c;

    printf("\nEnter the value of a b c:");
    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &c);

    float root1, root2;
    float D = b * b - 4 * a * c;

    if (D > 0)
    {
        root1 = (-b + sqrt(D)) / (2 * a);
        root2 = (-b - sqrt(D)) / (2 * a);
        printf("The roots are %f and %f", root1, root2);
    }
    else if (D == 0)
    {
        root1 = (-b / (2 * a));
        printf("The roots are %f and %f", root1);
    }
    else
    {
        float m = -D;
        m = sqrt(m);
        float c = -b / (2 * a);
        printf("The roots are %f+i%f and %f-i%f", c, m / (2 * a), c, m / (2 * a));
    }

    return 0;
}