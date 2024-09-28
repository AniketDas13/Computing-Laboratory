#include <stdio.h>
#include <stdlib.h>

void forward_backward_sort(int *arr, int n)
{
    for (int k = 0; k < n / 2; k++)
    {
        int start = k;
        int end = n - k;

        for (int i = start; i < end - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
            }
        }

        for (int i = end - 2; i > 0; i--)
        {
            if (arr[i] < arr[i - 1])
            {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
            }
        }
    }
}

int main()
{
    int *arr = (int *)malloc(100 * sizeof(int));
    int n = 0;

    while (EOF != scanf("%d", &arr[n]))
    {
        n++;
    }

    forward_backward_sort(arr, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}