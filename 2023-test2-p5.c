#include <stdio.h>
#include <math.h>

void largest_rectangle(double xa, double ya, double xb, double yb)
{
    if (ya != yb)
    {
        printf("INVALID INPUT\n");
        return;
    }

    double radius = (xb - xa) / 2.0;
    double xc = (xa + xb) / 2.0;
    double yc = ya;
    double h = radius / sqrt(2);

    printf("%.3f %.3f\n", xc - h, yc);
    printf("%.3f %.3f\n", xc - h, yc + h);
    printf("%.3f %.3f\n", xc + h, yc + h);
    printf("%.3f %.3f\n", xc + h, yc);
}

int main()
{
    double xa, ya, xb, yb;
    scanf("%lf %lf %lf %lf", &xa, &ya, &xb, &yb);
    largest_rectangle(xa, ya, xb, yb);

    return 0;
}