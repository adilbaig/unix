#include <stdio.h>
#include <time.h>

int main()
{
	time_t t;
	printf("Current time : %ld\n", (long) time(&t));
	printf("The same value : %ld\n", (long) t);

	/*struct timeval tv;
	int ret;

	ret = gettimeofday(&tv, NULL); //ALways keep the 2nd arg null. Its deprecated
	if(ret)
		perror("gettimeofday");
	else
		printf("s=%ld, us=%ld\n", (long)tv.tv_sec, (long)tv.tv_usec);*/

	/*
	 * Now get the current time of all 4 of the time sources
	 */
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

		// Get the from one of the clocks into a timespec struct
		int ret = clock_gettime(clocks[i], &res);
		if(ret)
			perror("clock_getres");
		else
			printf("clock=%d sec=%d nsec=%d\n", clocks[i], res.tv_sec, res.tv_nsec);
	}
}
