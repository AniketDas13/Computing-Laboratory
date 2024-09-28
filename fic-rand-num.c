#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
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

int main()
{
    srand(time(0));

    printf("Normal Number Sequence are \n");
    for (int i = 0; i < 100; i++)
    {
        Rnd_Num rd = normal();
        printf("Num1 and Num2: %f and %f \n", rd.num1, rd.num2);
    }

    return 0;
}