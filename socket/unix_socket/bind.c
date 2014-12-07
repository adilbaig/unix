#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include <stdio.h>


#define SOCKET_NAMESPACE_REGULAR "/tmp/adil_unix_socket_bind"

/**
 * Linux has a special feature: if the pathname for a UNIX domain socket begins
 * with a null byte \0, its name is not mapped into the filesystem. Thus it won’t
 * collide with other names in the filesystem. Also, when a server closes its
 * UNIX domain listening socket in the abstract namespace, its file is deleted;
 * with regular UNIX domain sockets, the file persists after the server closes it.
 */
#define SOCKET_NAMESPACE_LINUX "\0cool_linux_version"

int main()
{
	int fd;
	int size;
	struct sockaddr_un un;

	un.sun_family = AF_UNIX;
	strncpy(un.sun_path, SOCKET_NAMESPACE_LINUX, sizeof(un.sun_path)-1);

	if((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		perror("socket failed");
		return 1;
	}

	size  = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
	if(bind(fd, (struct sockaddr*)&un, size) < 0)
	{
		perror("bind failed");
		return 1;
	}

	printf("Unix domain socket bound");

	return 0;
}
