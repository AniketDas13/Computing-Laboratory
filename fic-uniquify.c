#include <stdio.h>
#include <stdlib.h>

int uniquify(int *arr, int n)
{
    int count = 0;
    int b[n];
    int i = 0;

    for (i = 0; i <= n - 2; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return -1;
        }
    }

    for (i = 0; i < n - 1; i++)
    {
        if (arr[i] != arr[i + 1])
        {
            b[count++] = arr[i];
        }
    }

    if (arr[n - 1] != arr[n - 2])
    {
        b[count++] = arr[n - 1];
    }

    for (i = 0; i < count; i++)
    {
        arr[i] = b[i];
    }

    return count;
}

int main()
{
    int len, i;

    printf("Enter the length of the array:");
    scanf("%d", &len);

    int *arr = (int *)malloc(len * sizeof(int));

    printf("\nEnter the array elements:");
    for (i = 0; i < len; i++)
    {
        int x;
        scanf("%d", &x);
        arr[i] = x;
    }

    int p = uniquify(arr, len);

    printf("The number of unique elements is %d", p);

    if (p != -1)
    {
        printf("\nPrinting the unique elements:");
        for (i = 0; i < p; i++)
        {
            printf("%d ", arr[i]);
        }
    }

    return 0;
}