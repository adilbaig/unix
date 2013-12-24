/**
 * Stores a series of vectors in a table.
 * Allows searching for a given vector by id, and retrieving its at a given position.
 */

/**
 * 	int* arr[8]; 	// An array of 8 pointer to integer.
	int (*arr)[8]; 	// A pointer to an array of integers
	int *(arr3[8]); // An array of 8 pointer to integer

	int* arr[8] == int *(arr3[8])
 */

/**
 * This table does not use malloc/realloc, but works with variable length arrays as defined in C99.
 * I've now stopped using it because it causes a stack overflow!
 */

/**
 * A Table struct stores a :
 *  - an array of pointers to a Vector
 *  - a length
 *  - current capacity
 */
struct Table {
	int length;
	int capacity;
	struct Vector** vectors;
};

void table_increase_capacity(struct Table *table, int capacity);

void table_init(struct Table *table) {
	table->length = 0;
	table->capacity = 100;

	// Allocate space for 100 pointers
	table->vectors = malloc(sizeof(size_t) * table->capacity);
}

void table_append(struct Table *table, struct Vector *vector) {
	// make sure there's room to expand into
	if (table->length >= table->capacity) {
		table_increase_capacity(table, 100);
	}

	//printf("table->length = %i table->capacity = %i \n", table->length, table->capacity);

	// append the value and increment table->length
	table->vectors[table->length++] = vector;
}

void table_increase_capacity(struct Table *table, int capacity) {
	// increase table->capacity and resize the allocated memory accordingly
	table->capacity += capacity;
	table->vectors = realloc(table->vectors, sizeof(size_t) * table->capacity);

	if(table->vectors == NULL) {
		perror("Could not realloc table->vectors");
		exit(1);
	}
}

struct Vector* table_get(struct Table *table, int index) {
	if (index >= table->length || index < 0) {
		printf("Index %d out of bounds for table of length %d\n", index,
				table->length);
		exit(1);
	}

	return table->vectors[index];
}

int table_get_values(struct Table *table, const char *search, char ***strings) {
	int pos = vector_find(table_get(table, 0), search);
	if(pos < 0) {
		return pos;
	}

	char **_tmp = malloc(sizeof(size_t) * table->length);
	printf("strings == '%x'\n", strings);
	for(int i=1; i < table->length; i++) {
		_tmp[i-1] = vector_get(table->vectors[i], pos);
	}

	*strings = _tmp;

	return pos;
}

void table_print(struct Table *table) {
	printf("Printing %i rows from table\n", table->length);

	for (int i = 0; i < table->length; i++) {
		printf("Index %i\n", i);
		vector_print(table_get(table, i));
	}
}

void table_free(struct Table *table) {
	for(int i=0; i < table->length; i++) {
		vector_free(table->vectors[i]);
	}

	free(table->vectors);
}
