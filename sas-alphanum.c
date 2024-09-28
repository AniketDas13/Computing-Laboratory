#include <stdio.h>
#include <string.h>

int main()
{
    int c;
    char curr;
    int count = -1;
    int max_count = -1;
    char max_char;

    while (EOF != (c = fgetc(stdin)))
    {
        if (c == ' ' || c == '\t')
        {
            continue;
        }

        if (curr != c)
        {
            if (count == -1)
            {
                curr = c;
                count = 1;
            }
            else
            {
                if (count == 1)
                {
                    printf("%c", curr);
                }
                else
                {
                    printf("%c%d", curr, count);
                }

                if (count > max_count)
                {
                    max_count = count;
                    max_char = curr;
                }

                curr = c;
                count = 1;
            }
        }
        else
        {
            count++;
        }
    }

    printf("\nThe maximum count of the charecter is %d and the charecter is %c", max_count, max_char);

    return 0;
}