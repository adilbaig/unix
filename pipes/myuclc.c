#include <ctype.h>
#include <stdio.h>

void main()
{
	int c;
	while((c = getchar()) != EOF) {
		if (isupper(c))
			c = tolower(c);

		if (putchar(c) == EOF)
			perror("putchar error");

		if (c == '\n')
			fflush(stdout);
	}
}
