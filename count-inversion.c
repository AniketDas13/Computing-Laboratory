#include <stdio.h>

int countInversions(int arr[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                printf("(%d, %d) ", arr[i], arr[j]);
                count++;
            }
        }
    }
    return count;
}

int main()
{
    int arr[] = {8, 4, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Inversions: ");
    int result = countInversions(arr, n);

    printf("\nTotal Inversions: %d\n", result);

    return 0;
}