#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *a)
{
    int length = strlen(a);

    for (int i = 0; i < length / 2; i++)
    {
        char temp;
        temp = a[i];
        a[i] = a[length - i - 1];
        a[length - i - 1] = temp;
    }
}

int main()
{
    int carry = 0;
    char number1[101];
    char number2[101];

    printf("\nEnter the first number:");
    scanf("%s", number1);
    printf("\nEnter the second number:");
    scanf("%s", number2);

    int m = strlen(number1);
    int n = strlen(number2);
    int i = 0;
    int j = 0;
    int *product = (int *)malloc((m + n) * sizeof(int));

    reverse(number1);
    reverse(number2);

    for (i = 0; i < m + n; i++)
    {
        product[i] = 0;
    }

    for (j = 0; j < n; j++)
    {
        carry = 0;
        for (i = 0; i < m; i++)
        {
            int digit1 = (number1[i] - '0');
            int digit2 = (number2[j] - '0');
            int sum = (product[i + j] + digit1 * digit2 + carry);
            product[i + j] = sum % 10;
            carry = sum / 10;
        }
        if (carry != 0)
        {
            product[i + j] = carry;
        }
    }

    char result[201];
    for (i = 0; i < m + n; i++)
    {
        result[i] = ('0' + product[i]);
    }

    reverse(result);
    printf("\nThe result of multiplication of 2 numbers is: %s", result);

    return 0;
}