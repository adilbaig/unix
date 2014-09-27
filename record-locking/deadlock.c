#include <stdio.h>
#include <fcntl.h>

/**
 * Advanced Programming In The Unix Environment, 2nd Ed
 * Pg 450
 */
#define writew_lock(fd, offset, whence, len) lock_reg(fd, F_SETLKW, F_WRLCK, offset, whence, len)

static int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;

	lock.l_type = type;
	lock.l_len = len;
	lock.l_whence = whence;
	lock.l_start = offset;

	return fcntl(fd, cmd, &lock);
}

static void lockabyte(const char *name, int fd, off_t offset)
{
	if (writew_lock(fd, offset, SEEK_SET, 1) < 1) {
		printf("%s: writew_lock error\n", name);
		return;
	}

	printf("%s : got the lock, byte %ld\n", name, offset);
}

int main(int argc, char *argv[])
{
	int fd;
	pid_t pid;

	/**
	 * Create a file and write two bytes to it
	 */
	if((fd = creat("/tmp/templock", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
		perror("creat error");
		return 1;
	}

	if(write(fd, "ab", 2) != 2) {
		perror("write error\n");
		return 1;
	}

	//TELL_WAIT();
	if ((pid = fork()) < 0) {
		perror("fork error");
		return 1;
	} else if (pid == 0) { //child
		lockabyte("child", fd, 0);
		//TELL_PARENT(getppid());
		//WAIT_PARENT();
		lockabyte("child", fd, 1);
	} else { //parent
		lockabyte("parent", fd, 1);
		//TELL_CHILD(getppid());
		//WAIT_CHILD();
		lockabyte("parent", fd, 0);
	}

	return 0;
}
