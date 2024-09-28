#include <stdio.h>
#include <math.h>
#include <stdlib.h>
typedef struct
{
    double num1;
    double num2;
} Rnd_Num;

Rnd_Num normal(void)
{
    double u1 = (rand() + 1.0) / (RAND_MAX + 2.0);
    double u2 = (rand() + 1.0) / (RAND_MAX + 2.0);
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * 3.14 * u2);
    double z1 = sqrt(-2.0 * log(u1)) * sin(2.0 * 3.14 * u2);

    Rnd_Num st;
    st.num1 = z0;
    st.num2 = z1;

    return st;
}

double normalCDF(double z)
{
    int count = 0;

    for (int i = 1; i <= 5000; i++)
    {
        Rnd_Num st = normal();

        if (st.num1 <= z)
        {
            count++;
        }

        if (st.num2 <= z)
        {
            count++;
        }
    }

    double value = (double)count / 10000;

    return value;
}
int main()
{
    double mu1, sigma1, mu2, sigma2, mu3, sigma3;

    printf("\nEnter the average and standard deviation of first way:");
    scanf("%lf", &mu1);
    scanf("%lf", &sigma1);
    printf("\nEnter the average and standard deviation of second way:");
    scanf("%lf", &mu2);
    scanf("%lf", &sigma2);
    printf("\nEnter the average and standard deviation of third way:");
    scanf("%lf", &mu3);
    scanf("%lf", &sigma3);

    double T;

    printf("\nEnter the value of T:");
    scanf("%lf", &T);

    double mean = mu1 + mu2 + mu3;
    double variance = (sigma1 * sigma1) + (sigma2 * sigma2) * (sigma3 * sigma3);
    double sd = sqrt(variance);
    double z_value = (T - mean) / sd;

    if (z_value >= 0)
    {
        printf("\nThe probability to reach is %.8lf", 1 - normalCDF(z_value));
    }
    else
    {
        printf("\nThe probability to reach is %.8lf", normalCDF(-z_value));
    }

    return 0;
}