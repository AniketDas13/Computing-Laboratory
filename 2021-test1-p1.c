#include <stdio.h>

int maxBricksSaved(int arr[], int n)
{
    int leftMax[n], rightMax[n];
    int savedBricks = 0;

    // Initialize the left and right maximum arrays
    leftMax[0] = arr[0];
    for (int i = 1; i < n; i++)
    {
        leftMax[i] = (arr[i] > leftMax[i - 1]) ? arr[i] : leftMax[i - 1];
    }

    rightMax[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        rightMax[i] = (arr[i] > rightMax[i + 1]) ? arr[i] : rightMax[i + 1];
    }

    // Calculate the total bricks saved
    for (int i = 0; i < n; i++)
    {
        int waterLevel = (leftMax[i] < rightMax[i]) ? leftMax[i] : rightMax[i];
        savedBricks += waterLevel - arr[i];
    }

    return savedBricks;
}

int main()
{
    int arr[100] = {0};
    int n = 0;

    // int arr[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    // int n = sizeof(arr) / sizeof(arr[0]);
    while (arr[n] = fgetc(stdin) != EOF)
    {
        n++;
    }

    printf("%d\n", maxBricksSaved(arr, n));

    return 0;
}