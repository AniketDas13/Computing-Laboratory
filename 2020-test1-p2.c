#include <stdio.h>

int findFirstNegative(int *arr, int size)
{
    int low = 0, high = size - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] < 0)
        {
            if (mid == 0 || arr[mid - 1] >= 0)
            {
                return mid;
            }
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return size;
}

int main()
{
    int n = 10;
    int arr[10] = {400, 11, 10, 5, 4, 3, 1, 0, -20, -100};

    int result = findFirstNegative(arr, n);
    printf("%d\n", result);

    return 0;
}