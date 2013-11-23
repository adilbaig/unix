#include <sys/types.h>
#include <sys/shm.h>

#define SHMKEY 75
#define K	1024
int shmid;

void cleanup();

main()
{
	int i, *pint;
	int *addr1, *addr2;

	for(i=0; i < 20; i++)
		signal(i, cleanup);

	shmid = shmget(SHMKEY, 128 * K, 0777|IPC_CREAT);
	addr1 = shmat(shmid, 0, 0);
	addr2 = shmat(shmid, 0, 0);

	printf("addr1 0x%x, addrs 0x%x\n", addr1, addr2);

	//Set the shared memory values in addr1 ..
	pint = addr1;
	for(i=0; i < 256; i++)
		*pint++ = i;

	//.. and read it off addr2
	pint = addr2;
	for(i=0; i < 256; i++)
		printf("index %d\tvalue %d\n", i, *pint++);

	pause();
}

void cleanup()
{
	shmctl(shmid, IPC_RMID, 0);
	exit(0);
}
