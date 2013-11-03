#include <signal.h>
#include <termio.h>
#include <sys/ioctl.h>
#include <stdio.h>

struct termio savetty;

void sigcatch();

void main()
{
	struct termio newtty;
	int nrd;
	char buf[32];
	signal(SIGINT, &sigcatch);

	if(ioctl(0, TCGETA, &savetty) == -1)
	{
		printf("ioctl failed: not a tty\n");
		exit(1);
	}

	newtty = savetty;
	newtty.c_lflag &= ~ICANON;
	newtty.c_lflag &= ~ECHO;
	newtty.c_cc[VMIN] = 5;
	newtty.c_cc[VTIME] = 100;

	if(ioctl(0, TCSETAF, &newtty) == -1)
	{
		printf("cannot put tty into raw mode\n");
		exit(1);
	}

	for(;;)
	{
		nrd = read(0, buf, sizeof(buf));
		buf[nrd] = 0;
		printf("read %d chars '%s'\n", nrd, buf);
	}

}

void sigcatch()
{
	ioctl(0, TCSETAF, &savetty);
	exit(1);
}
