/**
 * This file reads data into an mmap. Another process then reads that data and echoes it out
 */

#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "vector.c"
#include "table.c"


int main(int argc, char *argv[]) {

	//Read strings from a file and load them in memory
	//Access and read them from a given position

	FILE *stream = fopen(argv[1], "r");
	if (stream == NULL) {
		perror("Could not open file");
		exit(EXIT_FAILURE);
	}

	struct Table table;
	table_init(&table);

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while ((read = getline(&line, &len, stream)) != -1) {
	   struct Vector vector;
	   vector_init(&vector);
	   vectorize_csv(&vector, line, read); // we don't pass the new line char
	   vector_print(&vector);
	   table_append(&table, &vector);
	}

	free(line);
	fclose(stream);

	sleep(5);

	table_print(&table);

	printf("Get RIC\n");
	char **rez;
	if (table_get_values(&table, "RIC", rez) >= 0) {
		for (int i = 0; i < table.length - 1; i++)
			printf("'%s'\n", rez[i]);
	}/**/

	//table_free(&table);

	exit(EXIT_SUCCESS);
}


void vectorize_csv(struct Vector *vector, char *str, size_t length) {
	int l = 0;
	int last_comma = 0;

	//Go through *str char by char ..
	for (int i = 0; i < length; i++) {
		// .. when you hit one of [,\n] or end, process the remaining string into a vector entry
		if (str[i] == ',') {
			l = i - last_comma;
			//printf("%i) Address %x, '%s', Length = %i \n", i, &str[last_comma], &str[last_comma], l);
			vector_append(vector, &str[last_comma], l);
			last_comma = i + 1;
		}
	}

}
