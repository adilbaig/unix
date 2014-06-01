/*
 * thread-cleanup.c
 *
 *  Created on: 01-Jun-2014
 *      Author: adil
 */

#include <pthread.h>
#include <stdio.h>

void cleanup(void *arg)
{
	printf("cleanup : %s\n", (char *)arg);
}

void* thr_fn1(void *arg)
{
	printf("thread 1 started\n");
	pthread_cleanup_push(cleanup, "thread 1 cleanup handler 1");
	pthread_cleanup_push(cleanup, "thread 1 cleanup handler 2");
	printf("thread 1 push complete\n");

	if (arg)
		return((void *)1);

	printf("reached here\n");
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	return((void *)1);
}

void* thr_fn2(void *arg)
{
	printf("thread 2 started\n");
	pthread_cleanup_push(cleanup, "thread 2 cleanup handler 1");
	pthread_cleanup_push(cleanup, "thread 2 cleanup handler 2");
	printf("thread 2 push complete\n");

	if (arg)
		pthread_exit((void *)2);

	printf("thr_fn2 reached here\n");
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_exit((void *)2);
}

void main()
{
	int err;
	pthread_t tid1,tid2;
	void *tret;

	err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	if(err != 0)
		perror("can't create thread1");

	err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
	if(err != 0)
		perror("can't create thread2");

	err = pthread_join(tid1, &tret);
	if(err != 0)
		perror("can't join thread1");
	printf("thread 1 exit code : %d\n", (int)tret);

	err = pthread_join(tid2, &tret);
	if(err != 0)
		perror("can't join thread2");
	printf("thread 2 exit code : %d\n", (int)tret);

	exit(0);
}
