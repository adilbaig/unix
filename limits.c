/*
 * limits.c
 *
 *  Created on: 06-Mar-2014
 *      Author: adil
 */

#include <stdio.h>
#include <sys/resource.h>

int main()
{
    struct rlimit rlim;
    int ret;

    // Get the limit on 'core size'
    ret = getrlimit(RLIMIT_CORE, &rlim);
    if(ret == -1) {
        perror("getrlimit");
        return 1;
    }

    printf("RLIMIT_CORE limits: soft=%ld hard=%ld\n", rlim.rlim_cur, rlim.rlim_max);

    rlim.rlim_cur = 32 * 1024 * 1024; //32MB
    rlim.rlim_max = RLIM_INFINITY; //Leave it alone
    ret = setrlimit(RLIMIT_CORE, &rlim);
    if(ret == -1) {
        perror("setrlimit");
        return 1;
    }

    ret = getrlimit(RLIMIT_CORE, &rlim);
    if(ret == -1) {
        perror("getrlimit");
        return 1;
    }
    printf("RLIMIT_CORE limits: soft=%ld hard=%ld\n", rlim.rlim_cur, rlim.rlim_max);

}
