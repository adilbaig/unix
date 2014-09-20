#include <fcntl.h>
#include <stdio.h>

pid_t locktest(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	lock.l_type = type;
	lock.l_start = offset;
	lock.l_whence = whence;
	lock.l_len = len;

	if (fcntl(fd, F_GETLK, &lock) < 0)
		perror("fcntl failed!");

	if (lock.l_type == F_UNLCK)
		return 0;

	return lock.l_pid;
}

int main(int argc, char *argv[])
{
	if(argc < 2) {
		printf("%s [FILE]\n", argv[0]);
		printf("Check if a file is locked");
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	if(fd < 1) {
		perror("open error");
		return 1;
	}
	int l = locktest(fd, F_RDLCK, 0, SEEK_SET, 0);

	if(l == 0)
		printf("File is unlocked for reads\n");
	else
		printf("File has a read-lock by pid %d\n", l);

	return 0;
}
