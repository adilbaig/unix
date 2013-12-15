/**
 * This file reads data into an mmap. Another process then reads that data and echoes it out
 */

#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
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

	/*int fd = open(argv[1], O_RDONLY);
	if(fd == -1)
		perror("Could not open file");

	ssize_t curlen = 1024;
	char *buffer;
	char buf[1024];
	ssize_t ret;

	while((ret = read(fd, &buf, 1024)) != 0) {
		if(ret == -1) {
			if(errno == EINTR)
				continue;
			perror("read");
			break;
		}

		curlen += ret;
//		*buffer += buf;
		printf("%i bytes read.\n '%s'\n", ret, buf);
	}*/


	char *str = "RIC,TRBCIndCode,ratios._MktCap,ratios._OpMgnRPY,Company Name";

	struct Vector header;
	vector_init(&header);
	vectorize_csv(&header, str, strlen(str));

	//There can be an unlimited number of rows. We need a vector to manage all rows.
	str = "VOD.L,551020,48965.5,45684,Vodafone PLC";

	struct Vector row1;
	vector_init(&row1);
	vectorize_csv(&row1, str, strlen(str));

	str = "ATKW.L,,12345.5,99676,Atkins Group";
	struct Vector row2;
	vector_init(&row2);
	vectorize_csv(&row2, str, strlen(str));

	struct Table table;
	table_init(&table);
	table_append(&table, &header);
	table_append(&table, &row1);
	table_append(&table, &row2);
	table_print(&table);

	printf("Get TRBCIndCode\n");
	char **rez;
	if(table_get_values(&table, "TRBCIndCode", rez) >= 0) {
		for(int i=0; i < table.length-1; i++)
			printf("'%s'\n", rez[i]);
	}

	table_free(&table);
}

void vectorize_csv(struct Vector *vector, char *str, size_t length)
{
	int l=0;
	int last_comma = 0;
	for (int i = 0; i <= length; i++)
	{
		if(str[i] == ',' || str[i] == '\n' || i == length) {
			l = i - last_comma;
			char *_ptr = malloc (l + 1);
			memcpy(_ptr, &str[last_comma], l);
			vector_append(vector, _ptr);

			last_comma = i+1;
		}
	}
}

