#include <stdio.h>
#include <sys/wait.h>

/**
 * Filter program. Uses pipes to take user input and convert it to lowercase
 * INSTRUCTIONS: compile myuclc first.
 *
 * Advanced Programming in the Unix Environment. 2nd Ed
 * Figure 15.15
 */
#define MAXLINE 1024

void main()
{
	char line[MAXLINE];
	FILE *fpin;

	if ((fpin = popen("$PWD/myuclc", "r")) == NULL) {
		perror("popen failed");
		return;
	}

	while(1) {
		fputs("prompt> ", stdout);
		fflush(stdout);

		if(fgets(line, MAXLINE, fpin) == NULL) {
			break;
		}

		if(fputs(line, stdout) == EOF) {
			perror("fputs failed");
			return;
		}
	}

	if (pclose(fpin) == -1) {
		perror("pclose failed");
		return;
	}

	putchar('\n');
}
