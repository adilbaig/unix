#include <sys/types.h>
#include <sys/shm.h>

#define SHMKEY 75
#define K	1024
int shmid;

main()
{
	int i;
	int *addr;

	shmid = shmget(SHMKEY, 64 * K, 0777);
	addr  = shmat(shmid, 0, 0);
	printf("shmid %d, addr 0x%x\n", shmid, addr);

	//while(*addr == 0)
		;

	for(i=0; i < 256; i++)
		printf("%d\n", i, *addr++);

}
