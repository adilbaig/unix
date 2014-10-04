#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

/**
 * MMap Copying program. Is faster than read/write
 *
 * Advanced Programming in the Unix Environment. 2nd Ed
 * Figure 14.32
 */
int main(int argc, char* argv[])
{
	int fdin, fdout;
	void* src;
	void* dst;
	struct stat statbuf;

	if (argc != 3) {
		err(1, "usage %s <from file> <to file>", argv[0]);
	}

	if ((fdin = open(argv[1], O_RDONLY)) < 0) {
		err(1, "Can't open %s for reading", argv[1]);
	}

	if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC)) < 0) {
		err(1, "Can't open %s for writing", argv[2]);
	}

	if (fstat(fdin, &statbuf) < 0) {
		err(1, "fstat error");
	}

	// set size of output files
	if (lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1) {
		err(1, "lseek error");
	}

	if(write(fdout, "", 1) != 1) {
		err(1, "write error");
	}

	if((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED) {
		err(1, "mmap error for input");
	}

	if((dst = mmap(0, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, 0)) == MAP_FAILED) {
		err(1, "mmap error for input");
	}

	memcpy(dst, src, statbuf.st_size); //copy the file
	printf("%s copied to %s successfully\n", argv[1], argv[2]);
	return 0;
}
