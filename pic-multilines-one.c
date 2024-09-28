#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // Dynamically allocate an array of pointers for lines
    char **arr;
    int max_lines = 10;
    int max_chars = 80;
    arr = (char **)malloc(max_lines * sizeof(char *));

    // Allocate memory for each line
    for (int i = 0; i < max_lines; i++)
    {
        arr[i] = (char *)malloc(max_chars * sizeof(char));
    }

    // Read lines and store their length
    int length[max_lines];
    int count = 0;
    int line_count = 0;

    printf("Enter up to 10 lines of text (each no more than 80 characters):\n");

    while (line_count < max_lines && fgets(arr[line_count], max_chars, stdin))
    {
        // Remove the newline character from the end of the line if present
        int len = strlen(arr[line_count]);
        if (arr[line_count][len - 1] == '\n')
        {
            arr[line_count][len - 1] = '\0';
            len--;
        }
        length[line_count] = len;
        line_count++;
    }

    // Get user input for choices
    printf("\nEnter your choice: 1. Print even-numbered lines  2. Print odd-numbered lines: ");
    int choice1;
    scanf("%d", &choice1);

    printf("Print the lines in: 1. Reverse order  2. Original order: ");
    int choice2;
    scanf("%d", &choice2);

    // Print even or odd lines based on user choice
    int start = (choice1 == 1) ? 1 : 0; // Start at 1 for even, 0 for odd
    for (int i = start; i < line_count; i += 2)
    {
        if (choice2 == 1)
        {
            // Print in reverse order
            for (int j = length[i] - 1; j >= 0; j--)
            {
                printf("%c", arr[i][j]);
            }
        }
        else
        {
            // Print in original order
            printf("%s", arr[i]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < max_lines; i++)
    {
        free(arr[i]);
    }
    free(arr);

    return 0;
}