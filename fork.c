#include <stdio.h>;
#include <fcntl.h>;

int main()
{
	printf("Hello \n");
	int c=0;
	while(c++ < 10) {
		sleep(10);

		if(fork() == 0) {
			printf("World \n");
		}
	}
}
