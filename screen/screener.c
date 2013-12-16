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

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("Could not open file");
		exit(1);
	}

	char buf[1024];
	ssize_t ret;

	struct Table table;
	table_init(&table);

	while ((ret = read(fd, &buf, 1024)) != 0) {
		if (ret == -1) {
			if (errno == EINTR)
				continue;
			perror("read");
			break;
		}

		buffer_append(&buf, ret);

		struct Vector vector;
		if(process_buffer(&vector) >= 0) {
			table_append(&table, &vector);
		}
	}

	printf("Reached here without errors\n");

	table_print(&table);

	printf("Get TRBCIndCode\n");
	char **rez;
	if (table_get_values(&table, "TRBCIndCode", rez) >= 0) {
		for (int i = 0; i < table.length - 1; i++)
			printf("'%s'\n", rez[i]);
	}

	table_free(&table);
}

char *buffer = NULL;
unsigned int buffer_capacity = 0;
unsigned int buffer_length = 0;
void buffer_append(char *buf, int len) {

	int cap = buffer_capacity - buffer_length;

	if (cap < len) {
		printf("REALLOCATION\n");
		buffer_capacity += len;
		buffer = (char*)realloc(buffer, buffer_capacity);
	}

	printf("%x, %x\n", buffer, buffer + buffer_length);

	//Read len bytes of *buf, and copy it to buffer.
	memcpy(buffer + buffer_length, buf, len);
	buffer_length += len;
}

int process_buffer(struct Vector *vector) {

	//Iterate through each character, finding a \n
	for(int i=0 ; i < buffer_length; i++) {
		if(buffer[i] == '\n') {
			vector_init(vector);

			//printf("%i. buffer '%.35s'", i, buffer);
			i++;
			vectorize_csv(vector, buffer, i);
			buffer = buffer + i;
			return i;
		}
	}

	return -1;
}

void vectorize_csv(struct Vector *vector, char *str, size_t length) {
	int l = 0;
	int last_comma = 0;
	for (int i = 0; i < length; i++) {

		printf("%i = '%c'\n", i, str[i]);
		if (str[i] == ',' || str[i] == '\n' || i == length) {

			l = i - last_comma;
			char *_ptr = malloc(l + 1);

			memcpy(_ptr, &str[last_comma], l);
			printf("last_comma = %i, l = %i, str = '%c', _ptr = '%s'\n", last_comma, l, str[last_comma], _ptr);

			vector_append(vector, _ptr);

			last_comma = i + 1;
		}
	}
}
