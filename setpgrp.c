#include <signal.h>

main()
{
	register int i;

	setpgrp();
	for(i=0; i < 10; i++) {
		printf("%u)", i);
		if(fork() == 0)
		{
			//For odd numbered children, set a new process group id
			if(i & 1)
				setpgrp();

			printf("pid = %d pgrp = %d \n", getpid(), getpgrp());
			pause();
		}
	}

	kill(0, SIGINT);
}
