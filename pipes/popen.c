#include <stdio.h>
#include <sys/wait.h>

/*
 * popen.c
 *
 * Creating pipes with children using popen
 *
 * Advanced Programming in the Unix Environment. 2nd Ed
 * Figure 15.11
 *
 *  Created on: 04-Oct-2014
 *      Author: adil
 */

#define PAGER "${PAGER:-less}"

int main(int argc, char* argv[])
{
	char line[1024];
	FILE *fpin, *fpout;

	if (argc != 2) {
		err(1, "Usage : %s <pathname>", argv[0]);
	}

	if ((fpin = fopen(argv[1], "r")) == NULL) {
		err(1, "fopen failed");
	}

	if ((fpout = popen(PAGER, "w")) == NULL) {
		err(1, "popen failed");
	}

	// copy argv[1] to pager

	while(fgets(line, 1024, fpin) != NULL) {
		if (fputs(line, fpout) == EOF) {
			err(1, "fputs failed");
		}
	}

	if (ferror(fpin)) {
		err(1, "fgets error");
	}

	if (pclose(fpout) == -1) {
		err(1, "pclose error");
	}

	return 0;
}
