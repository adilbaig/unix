/*
 * headers.c
 *
 *  Created on: 14-Dec-2013
 *      Author: adil
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *name;
} HEADER;

HEADER *array;
int num_elements = 0;
int num_allocated = 0;

int addToArray(HEADER item)
{
	if(num_elements == num_allocated)
	{
		//Allocate in batches of 10
		num_allocated += 10;

		//Make the reallocation transactional by using a temporary variable first
		void *_tmp = realloc(array, (num_allocated * sizeof(HEADER)));

		if(!_tmp)
		{
			perror("ERROR: Couldn't realloc memory");
			return -1;
		}

		array = (HEADER*)_tmp;
	}

	array[num_elements++] = item;
	return num_elements;
}
