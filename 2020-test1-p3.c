#include <stdio.h>

// Function to reverse a number
int reverse(int num)
{
    int rev = 0;
    while (num > 0)
    {
        rev = rev * 10 + num % 10;
        num /= 10;
    }

    return rev;
}

// Function to check if a number is a conjoined twin number
int isConjoinedTwin(int num)
{
    for (int i = 12; i < num; i++)
    {
        int rev = reverse(i);
        if (i + rev == num)
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);

    int found = 0;
    for (int i = 33; i <= n; i++)
    {
        if (isConjoinedTwin(i))
        {
            printf("%d ", i);
            found = 1;
        }
    }

    if (!found)
    {
        printf("None\n");
    }

    return 0;
}