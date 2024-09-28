#include <stdio.h>

int main()
{
	int c;
	// FILE* fptr;
	// fptr = fopen("getc-input.txt", "r");

	while (EOF != (c = fgetc(stdin)))
	{
		if (c == '\n')
			continue;
		printf("%c:%d ", c, c);
	}
}