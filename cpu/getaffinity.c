#define _GNU_SOURCE

#include <stdio.h>
#include <sched.h>

void main()
{
    cpu_set_t set;
    int ret,i;

    //Zero out the struct
    CPU_ZERO(&set);
    //Get the processor affinity for this process
    ret = sched_getaffinity(0, sizeof(cpu_set_t), &set);
    if(ret == -1)
        perror("sched_getaffinity");

    /*
     * CPU_SETSIZE is the number of processors that can be represented by cpu_set_t
     */
    for(i=0; i < CPU_SETSIZE; i++)
    {
        int cpu;

        cpu = CPU_ISSET(i, &set);
        if(cpu)
            printf("cpu=%i is %s\n", i, cpu ? "set" : "unset");
    }
}
