#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "helper.c"

void doprocessing();


int main(int argc, char *argv[])
{
    int newsockfd, clilen, pid;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    printf("%d", argc);

    if(argc < 2)
    {
    	perror("Usage : a.out IP_ADDRESS");
    	exit(1);
    }

    for(int i=0; i < argc; i++)
    {
    	printf("%d : %s\n", i, argv[i]);
    }

    int sockfd = getSocket(argv[1], 5001);

    /* Now start listening for the clients, here
     * process will go in sleep mode and will wait
     * for the incoming connection
     */
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(1);
        }

        /* Create child process */
        pid = fork();
        if (pid < 0)
        {
            perror("ERROR on fork");
            exit(1);
        }

        if (pid == 0)
        {
            /* This is the client process */
            close(sockfd);
            doprocessing(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    } /* end of while */
}

//The static keyword makes this function private to this file only.
static void doprocessing (int sock)
{
    int n;
    char buffer[256] = {0};

    //bzero(buffer,256);

    n = read(sock,buffer,255);
    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(1);
    }
    printf("Here is the message: %s\n", buffer);

    n = write(sock, buffer, n);
    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }

    exit(0);
}
