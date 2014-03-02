#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void main()
{
    int ret, val;

    //Get nice value
    val = nice(0);

    printf("Current nice value is %d\n", val);

    // We want a nice value of 10
    val = 10 - val;

    // -1 is a valid nice return value, and an error. So zero out errno first
    errno=0;

    ret = nice(val);
    if(ret == -1 && errno != 0)
        perror("nice");
    else
        printf("nice value is now %d\n", ret);
}
