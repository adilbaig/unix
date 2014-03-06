/*
 * scheduler.c
 *
 *  Created on: 06-Mar-2014
 *      Author: adil
 */

#include <sched.h>
#include <stdio.h>

void main()
{
    int policy;

    policy = sched_getscheduler(0);

    switch(policy) {
    case SCHED_OTHER :
        printf("Scheduler policy is normal");
        break;
    case SCHED_RR:
        printf("Scheduler policy is round-robin");
        break;
    case SCHED_FIFO:
        printf("Scheduler policy is FIFO");
        break;
    case -1 :
        perror("sched_getscheduler");
        break;
    default :
        fprintf(stderr, "Unknown policy!");
    }

    printf("\n");

    /*
     * Get the priority of the current process.
     * This is always 0 for non-realtime processes
     */
    struct sched_param sp;
    if(sched_getparam(0, &sp)  == -1) {
        perror("sched_getparam");
        return;
    }
    printf("Priority is %d \n", sp.__sched_priority);

    /*
     * Get the range of priorities for a given scheduling policy
     */
    int min, max;
    min = sched_get_priority_min(SCHED_RR);
    if(min == -1) {
        perror("sched_get_priority_min");
        return;
    }

    max = sched_get_priority_max(SCHED_RR);
    if(max == -1) {
        perror("sched_get_priority_max");
        return;
    }

    printf("SCHED_RR priority range is %d - %d \n", min, max);
}
