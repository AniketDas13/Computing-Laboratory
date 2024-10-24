#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void z_curve_aux(int **arr, int i, int j, int n)
{
    if (n == 0)
    {
        printf("%d ", arr[i][j]);
        return;
    }
    else if (n == 1)
    {
        printf("%d ", arr[i][j]);
        printf("%d ", arr[i][j + 1]);
        printf("%d ", arr[i + 1][j]);
        printf("%d ", arr[i + 1][j + 1]);
        return;
    }

    z_curve_aux(arr, i, j, n - 1);
    z_curve_aux(arr, i, j + (1 << (n - 1)), n - 1);
    z_curve_aux(arr, i + (1 << (n - 1)), j, n - 1);
    z_curve_aux(arr, i + (1 << (n - 1)), j + (1 << (n - 1)), n - 1);

    /*int num = pow(2, n - 1);
    z_curve_aux(arr, i, j, size - 1);
    z_curve_aux(arr, i + num, j, size);
    z_curve_aux(arr, i, j + num, size - 1);
    z_curve_aux(arr, i + num, j + num, size - 1);*/
}

void z_curve(int **arr, int m)
{
    int ind = pow(2, m - 1);
    z_curve_aux(arr, 0, 0, m - 1);
    z_curve_aux(arr, 0, ind, m - 1);
    z_curve_aux(arr, ind, 0, m - 1);
    z_curve_aux(arr, ind, ind, m - 1);
    return;
}

int main()
{
    int m;
    scanf("%d", &m);

    int temp = pow(2, m);
    int count = 0;
    int **arr = (int **)malloc(temp * sizeof(int *));

    for (int i = 0; i < temp; i++)
    {
        arr[i] = (int *)malloc(temp * sizeof(int));
    }

    for (int i = 0; i < temp; i++)
    {
        for (int j = 0; j < temp; j++)
        {
            count++;
            arr[i][j] = count;
        }
    }

    printf("The Z-Curve order of elements:\n");
    z_curve(arr, m);

    return 0;
}