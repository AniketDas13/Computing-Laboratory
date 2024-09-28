#include <stdio.h>
#include <string.h>
#include <string.h>
#include <ctype.h>

int main()
{
	int inword = 0;
	int vowel_cnt = 0;
	int word_cnt = 0;
	int c;

	while (EOF != (c = fgetc(stdin)))
	{
		if (isalnum(c))
		{
			if (c == 'A' || c == 'a' || c == 'E' || c == 'e' || c == 'I' || c == 'i' || c == 'O' || c == 'o' || c == 'U' || c == 'u')
			{
				vowel_cnt++;
			}
			inword = 1;
		}
		else
		{
			if (inword == 1)
			{
				word_cnt++;
			}
			inword = 0;
		}
	}

	printf("The vowel count is %d and the word count is %d", vowel_cnt, word_cnt);

	return 0;
}