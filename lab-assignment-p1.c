#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double x, y;
} Point;

int calcIntersection(Point f1, Point f2, Point g1, Point g2, Point *p_intersect)
{
    double m1 = (f2.y - f1.y) / (f2.x - f1.x);
    double m2 = (g2.y - g1.y) / (g2.x - g1.x);
    double c1 = f1.y - m1 * f1.x;
    double c2 = g1.y - m2 * g1.x;

    if (m1 == m2)
        return 0;

    double x = (c2 - c1) / (m1 - m2);
    if (x >= fmax(f1.x, g1.x) && x <= fmin(f2.x, g2.x))
    {
        double y = m1 * x + c1;
        p_intersect->x = x;
        p_intersect->y = y;
        return 1;
    }

    return 0;
}

int isSeparable(Point *f, Point *g, int m, int n, double a, double b)
{
    if (f[0].x > g[n - 1].x || f[m - 1].x < g[0].x || a < fmax(f[0].x, g[0].x) || b > fmin(f[m - 1].x, g[n - 1].x))
        return 0;

    for (int i = 0; i < m - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            double f1_x = f[i].x, f2_x = f[i + 1].x;
            double f1_y = f[i].y, f2_y = f[i + 1].y;
            double g1_x = g[j].x, g2_x = g[j + 1].x;
            double g1_y = g[j].y, g2_y = g[j + 1].y;

            Point p_intersect;
            int has_intersection = calcIntersection((Point){f1_x, f1_y}, (Point){f2_x, f2_y}, (Point){g1_x, g1_y}, (Point){g2_x, g2_y}, &p_intersect);

            double x_intersect = p_intersect.x;
            if (has_intersection && x_intersect >= fmax(f1_x, g1_x) && x_intersect <= fmin(f2_x, g2_x) && x_intersect >= a && x_intersect <= b)
                return 0;
        }
    }

    return 1;
}

double calcArea(Point *f, Point *g, int m, int n, double a, double b)
{
    double total_area = 0.0;

    for (int i = 0; i < m - 1; i++)
    {
        double f1_x = f[i].x, f2_x = f[i + 1].x;
        double f1_y = f[i].y, f2_y = f[i + 1].y;

        if (f2_x < a || f1_x > b)
            continue;

        double start_tmpx = fmax(a, f1_x);
        double end_tmpx = fmin(b, f2_x);

        for (int j = 0; j < n - 1; j++)
        {
            double g1_x = g[j].x, g2_x = g[j + 1].x;
            double g1_y = g[j].y, g2_y = g[j + 1].y;

            if (g2_x < start_tmpx || g1_x > end_tmpx)
                continue;

            double start_x = fmax(start_tmpx, g1_x);
            double end_x = fmin(end_tmpx, g2_x);

            double start_fy = f1_y + (f2_y - f1_y) * (start_x - f1_x) / (f2_x - f1_x);
            double end_fy = f1_y + (f2_y - f1_y) * (end_x - f1_x) / (f2_x - f1_x);
            double start_gy = g1_y + (g2_y - g1_y) * (start_x - g1_x) / (g2_x - g1_x);
            double end_gy = g1_y + (g2_y - g1_y) * (end_x - g1_x) / (g2_x - g1_x);

            Point p_intersect;
            int has_intersection = calcIntersection((Point){f1_x, f1_y}, (Point){f2_x, f2_y}, (Point){g1_x, g1_y}, (Point){g2_x, g2_y}, &p_intersect);

            double h1 = fabs(start_fy - start_gy);
            double h2 = fabs(end_fy - end_gy);

            if (has_intersection && p_intersect.x >= start_x && p_intersect.x <= end_x)
            {
                total_area += 0.5 * h1 * (p_intersect.x - start_x) + 0.5 * h2 * (end_x - p_intersect.x);
            }
            else
            {
                total_area += 0.5 * (h1 + h2) * (end_x - start_x);
            }
        }
    }

    return total_area;
}

int main()
{
    int m, n;
    double a, b;

    scanf("%d", &m);
    Point *f = (Point *)malloc(m * sizeof(Point));
    for (int i = 0; i < m; i++)
    {
        scanf("%lf %lf", &f[i].x, &f[i].y);
    }

    scanf("%d", &n);
    Point *g = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++)
    {
        scanf("%lf %lf", &g[i].x, &g[i].y);
    }

    scanf("%lf %lf", &a, &b);

    if (isSeparable(f, g, m, n, a, b))
        printf("SEPARABLE");
    else
        printf("NOT SEPARABLE");

    double area = calcArea(f, g, m, n, a, b);
    if (area != 0)
        printf(" %.4lf\n", calcArea(f, g, m, n, a, b));
    else
        printf(" UNDEFINED\n");

    return 0;
}