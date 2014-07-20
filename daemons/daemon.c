#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main()
{
    pid_t pid;
    int i;

    /*Step 1: Create a new process ..*/
    pid = fork();
    if(pid == -1)
        return -1;
    else if(pid != 0) // .. and exit the parent succesfully.
        exit (EXIT_SUCCESS);

    /* Create a new session and process group */
    if(setsid() == -1)
        return -1;

    /* Set the working directory to root. That's good manners */
    if(chdir("/") == -1)
        return -1;

    /* Close all open files. NR_OPEN is overkill, but works */
    for(i=0; i < 3; i++)
        close(i);

    /*
     * redirect 0,1,2 to /dev/null
     */
    open("/dev/null", O_RDWR);  //stdin
    dup(0); // stdout
    dup(0); // stderr

    // We are a DEAMON!

    //good. Or you could have used the function : int daemon(int nochdir, int noclose);

    return 0;
}
