#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to convert 8-bit binary string to a signed integer
int binaryToDecimal(const char *binary)
{
    int value = 0;
    int isNegative = (binary[0] == '1'); // Check the sign bit

    // Convert to decimal (unsigned)
    for (int i = 0; i < 8; i++)
    {
        value = (value << 1) | (binary[i] - '0');
    }

    // If negative, compute the two's complement
    if (isNegative)
    {
        value = value - (1 << 8); // Subtract 2^8
    }

    return value;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("NIL\n");
        return 0;
    }

    int numbers[argc - 1];
    int count = 0;

    // Convert input binary strings to signed integers
    for (int i = 1; i < argc; i++)
    {
        numbers[count++] = binaryToDecimal(argv[i]);
    }

    int found = 0;

    // Check for NEARLY MIRROR pairs
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (i != j && numbers[i] < 0 && numbers[j] > 0)
            {
                if (abs(numbers[i]) - numbers[j] == 1)
                {
                    printf("%s %s\n", argv[i + 1], argv[j + 1]);
                    found = 1;
                }
            }
        }
    }

    if (!found)
    {
        printf("NIL\n");
    }

    return 0;
}