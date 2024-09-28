#include <stdio.h>
#include <string.h>

void reverse(char *str)
{
    int len = strlen(str);
    int i;

    for (i = 0; i < len / 2; i++)
    {
        char temp;
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main()
{
    char num1[100], num2[100], result[101];
    char op, a;

    scanf("%s", num1);
    scanf("%s", num2);
    scanf("%c", &a);
    scanf("%c", &op);

    if (op == '+')
    {
        reverse(num1);
        reverse(num2);

        int len1 = strlen(num1), len2 = strlen(num2);
        int i = 0, j = 0, carry = 0, k = 0;

        while (i < len1 && j < len2)
        {
            int digit1 = (num1[i++] - '0');
            int digit2 = (num2[j++] - '0');
            int sum = digit1 + digit2 + carry;
            int rem = (sum % 10);
            carry = sum / 10;
            result[k++] = ('0' + rem);
        }

        if (i == len1)
        {
            while (j < len2)
            {
                int digit = (num2[j++] - '0');
                int sum = digit + carry;
                int rem = sum % 10;
                carry = sum / 10;
                result[k++] = rem + '0';
            }
        }

        if (j == len2)
        {
            while (i < len1)
            {
                int digit = (num1[i++] - '0');
                int sum = digit + carry;
                int rem = sum % 10;
                carry = sum / 10;
                result[k++] = rem + '0';
            }
        }

        if (carry != 0)
        {
            result[k] = (carry + '0');
        }

        int len = strlen(result);

        i = len - 2;
        while (i >= 0)
        {
            printf("%c", result[i]);
            i--;
        }
    }
    else if (op == '-')
    {
        reverse(num1);
        reverse(num2);

        int len1 = strlen(num1), len2 = strlen(num2);
        int i = 0, j = 0, carry = 0, k = 0;

        while (i < len1 && j < len2)
        {
            int digit1 = (num1[i++] - '0');
            int digit2 = (num2[j++] - '0');
            int sum;

            if ((digit1 + carry) >= (digit2))
            {
                sum = digit1 + carry - digit2;
                carry = 0;
            }
            else if ((digit1 + carry) < digit2)
            {
                sum = 10 + (digit1 + carry) - digit2;
                carry = -1;
            }

            int rem = (sum % 10);
            result[k++] = ('0' + rem);
        }

        if (i == len1)
        {
            while (j < len2)
            {
                int digit = (num2[j++] - '0');
                int sum;

                if ((carry - digit) >= 0)
                {
                    sum = carry - digit;
                    carry = 0;
                }
                else
                {
                    sum = 10 + carry - digit;
                    carry = -1;
                }

                int rem = sum % 10;
                result[k++] = rem + '0';
            }
        }

        if (j == len2)
        {
            while (i < len1)
            {
                int digit = (num1[i++] - '0');
                int sum;

                if (carry + digit >= 0)
                {
                    sum = carry + digit;
                    carry = 0;
                }
                else
                {
                    sum = 10 + carry + digit;
                    carry = -1;
                }

                int rem = sum % 10;
                result[k++] = rem + '0';
            }
        }

        if (carry != 0)
        {
            result[k] = (-carry + '0');
            printf("-");
        }

        int len = strlen(result);

        i = len - 1;
        while (i >= 0)
        {
            printf("%c", result[i]);
            i--;
        }
    }

    return 0;
}