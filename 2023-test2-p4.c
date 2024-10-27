#include <stdio.h>
#include <string.h>

#define MAX_WIDTH 80

void format_text()
{
    char word[81];
    int line_length = 0;

    while (scanf("%80s", word) != EOF) // Ctrl + Z + Enter (Win) or Ctrl + D (Lin)
    {
        int word_len = strlen(word);

        if (line_length + word_len > MAX_WIDTH)
        {
            printf("\n");
            line_length = 0;
        }

        if (line_length > 0)
        {
            printf(" ");
            line_length++;
        }

        printf("%s", word);
        line_length += word_len;
    }
    printf("\n");
}

int main()
{
    format_text();

    return 0;
}