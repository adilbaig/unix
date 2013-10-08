#include <fcntl.h>
#include <unistd.h>

int main()
{
	int status;

	if(fork() == 0) {
		execl("/bin/date", "date", 0);
		sleep(10);
	}

	wait(&status);
}
