#include <stdio.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char *s)
{
	pid_t pid;
	pthread_t  tid;

	pid = getpid();
	tid = pthread_self();

	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid, (unsigned int)tid, (unsigned int)tid);
}

void* thr_fn(void *arg)
{
	printids("new thread : ");
	return (void*)0;
}

void main()
{
	int err;

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	if(err != 0)
		perror("Can't create thread");


	printids("Main thread : ");

	/**
	 * The order of thread exceution is not fixed. If i don't sleep here
	 * the child may not get the chance to print it's ids
	 */
	sleep(1);
	exit(0);
}
