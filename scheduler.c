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
}
