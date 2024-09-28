#include <stdio.h>
#include <string.h>

int isValidTernary(char *statement)
{
    int count = 0;

    for (int i = 0; statement[i] != '\0'; i++)
    {
        if (statement[i] == '?')
            count++;
        else if (statement[i] == ':')
            count--;
        if (count < 0)
            return 0;
    }

    if (count > 0)
        return 0;

    return 1;
}

int main()
{
    char statement[100];

    fgets(statement, 100, stdin);

    if (statement[strlen(statement) - 1] == '\n')
    {
        statement[strlen(statement) - 1] = '\0';
    }

    if (isValidTernary(statement))
    {
        printf("VALID\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}