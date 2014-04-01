/*
 * clocks.c
 *
 *  Created on: 01-Apr-2014
 *      Author: adil
 */

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main()
{
	clockid_t clocks[] = {
		CLOCK_REALTIME,
		CLOCK_MONOTONIC,
		CLOCK_PROCESS_CPUTIME_ID,
		CLOCK_THREAD_CPUTIME_ID,
		(clockid_t) - 1
	};
	int i;

	for(i=0; clocks[i] != (clockid_t) - 1; i++)
	{
		struct timespec res;

		int ret = clock_getres(clocks[i], &res);
		if(ret)
			perror("clock_getres");
		else
			printf("clock=%d sec=%d nsec=%d\n", clocks[i], res.tv_sec, res.tv_nsec);
	}
}
