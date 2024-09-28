#include <stdio.h>
#include <stdlib.h>

// Function to compare two integers for descending order sorting
int compare(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

// Function to check if a number is divisible by 3
int isMultipleOfThree(int *digits, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += digits[i];
    }

    return (sum % 3 == 0);
}

// Function to construct the largest number possible from digits
int largestNumber(int *digits, int size)
{
    int num = 0;
    for (int i = 0; i < size; i++)
    {
        num = num * 10 + digits[i];
    }

    return num;
}

int main()
{
    int n;
    scanf("%d", &n);

    int maxMultiple = -1;
    int winners[100];
    int winnerCount = 0;

    for (int i = 1; i <= n; i++)
    {
        int k;
        int digits[100];

        scanf("%d", &k);
        for (int j = 0; j < k; j++)
        {
            scanf("%d", &digits[j]);
        }

        qsort(digits, k, sizeof(int), compare); // Sort digits in descending order

        if (isMultipleOfThree(digits, k))
        {
            int num = largestNumber(digits, k);
            if (num > maxMultiple)
            {
                maxMultiple = num;
                winners[0] = i; // Reset winner list
                winnerCount = 1;
            }
            else if (num == maxMultiple)
            {
                winners[winnerCount++] = i; // Add to winner list
            }
        }
    }

    if (winnerCount > 0)
    {
        for (int i = 0; i < winnerCount; i++)
        {
            printf("%d ", winners[i]);
        }
        printf("\n");
    }
    else
    {
        printf("None\n");
    }

    return 0;
}