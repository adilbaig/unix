#include <signal.h>

char *cp;
int callno = 0;

void catcher(int signo)
{
	callno++;
	printf("Caught sig %d %dth call at addr %u\n", signo, callno, cp);
	cp = sbrk(2);
	printf("Curr brk value %u\n", cp);
	signal(SIGSEGV, catcher);
}

int main()
{
	signal(SIGSEGV, catcher);
	cp = sbrk(0);

	printf("Original brk value %u\n", cp);

	//for(int i=0; i < 1000; i++) {
	for(;;) {
		*cp++ = 1;
		//printf("Incr %u\n", cp);
	}
}
