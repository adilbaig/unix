#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int signum)
{
    printf("Received signal %d\n", signum);
}

int main()
{
    signal(SIGINT, sig_handler);
    sleep(10); // This is your chance to press CTRL-C
    return 0;
}
