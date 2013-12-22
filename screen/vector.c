#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

struct Vector {
	int length; // slots used so far
	int capacity; // total available slots
	char **data; // array of strings
};

void vector_init(struct Vector *vector) {
	vector->length = 0;
	vector->capacity = 100;

	// Allocate space for vector_CAPACITY_BLOCK numbers if pointers
	vector->data = malloc(sizeof(size_t) * vector->capacity);
}

/**
 * memcpy *value with l length to *vector
 */
void vector_append(struct Vector *vector, const char *value, size_t l) {
	// make sure there's room to expand into
	if (vector->length >= vector->capacity) {
		vector_increase_capacity(vector, 100);
	}

	char *_ptr = strndup(value, l);

	// append the value and increment vector->length
	vector->data[vector->length++] = _ptr;
}

char* vector_get(struct Vector *vector, int index) {
	if (index >= vector->length || index < 0) {
		printf("Index %d out of bounds for vector of length %d\n", index,
				vector->length);
		exit(1);
	}
	return vector->data[index];
}


int vector_find(struct Vector *vector, const char value[])
{
	for(int i = 0; i < vector->length; i++)
	{
		//printf("'%s' == '%s'. CMP = %i\n", vector->data[i], value, strcmp(vector->data[i], value));

		if(strcmp(vector->data[i], value) == 0)
			return i;
	}

	return -1;
}

//static == (private in PHP)
void vector_increase_capacity(struct Vector *vector, int capacity) {
	// increase vector->capacity and resize the allocated memory accordingly
	vector->capacity += capacity;
	vector->data = realloc(vector->data, sizeof(size_t) * vector->capacity);
}

void vector_print(struct Vector *vector) {
	printf("Printing %i values from row\n", vector->length);

	for (int i = 0; i < vector->length; i++) {
		printf("%i '%s'\n", i, vector_get(vector, i));
	}
}

void vector_free(struct Vector *vector) {
	free(vector->data);
}