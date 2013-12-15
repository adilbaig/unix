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
 */
struct Table {
	int length;
	int capacity;
	struct Vector* vector[];
};

void table_init(struct Table *table) {
	table->length = 0;
	table->capacity = 100;

	// Allocate space for 100 pointers
	table->vector[sizeof(size_t) * table->capacity];
}

void table_append(struct Table *table, struct Vector *vector) {
	// make sure there's room to expand into
	table_increase_capacity(table, 100);

	// append the value and increment table->length
	table->vector[table->length++] = vector;
}

struct Vector* table_get(struct Table *table, int index) {
	if (index >= table->length || index < 0) {
		printf("Index %d out of bounds for table of length %d\n", index,
				table->length);
		exit(1);
	}

	return table->vector[index];
}

int table_get_values(struct Table *table, const char search[], char **strings) {
	int pos = vector_find(table->vector[0], search);
	if(pos < 0) {
		return pos;
	}

	for(int i=1; i < table->length; i++)
	{
		strings[i-1] = vector_get(table->vector[i], pos);
	}

	return pos;
}

void table_increase_capacity(struct Table *table, int capacity) {
	if (table->length >= table->capacity) {

		// increase table->capacity and resize the allocated memory accordingly
		table->capacity += capacity;
		table->vector[sizeof(size_t) * table->capacity];
	}
}

void table_print(struct Table *table) {
	printf("Printing %i rows from table\n", table->length);

	for (int i = 0; i < table->length; i++) {
		struct Vector *vector = table_get(table, i);
		vector_print(vector);
	}
}

void table_free(struct Table *table) {
	for(int i= 0; i < table->length; i++)
		vector_free(table->vector[i]);
}
