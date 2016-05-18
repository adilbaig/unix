#include <stdio.h>


int bss[1000];
int data = 100;

void main()
{
	int i;
	printf("The stack top is near %p\n", &i);
	printf("The data top is near %p\n", &data);
	printf("The bss top is near %p\n", &bss);
}
