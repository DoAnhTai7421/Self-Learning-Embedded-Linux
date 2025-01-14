#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 10 
#define SOCK_PATH "./sock_dgram"

int main(int argc, char *argv[])
{    
	struct sockaddr_un claddr;
    int fd, optval;
    size_t msgLen;
    ssize_t numBytes;
    char resp[BUF_SIZE];
	
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);      
    if (fd == -1)
		return 1;
	
	memset(&claddr, 0, sizeof(struct sockaddr_un)); 
    claddr.sun_family = AF_UNIX;
    strncpy(claddr.sun_path, SOCK_PATH, sizeof(claddr.sun_path)-1);
	
	// optval = 1;
    // setsockopt(fd, SOL_SOCKET, SO_PASSCRED, &optval, sizeof(optval));
	
	msgLen = strlen(argv[1]);
	if(sendto(fd, argv[1], msgLen, 0, (struct sockaddr *)&claddr, sizeof(struct sockaddr_un)) != msgLen)
		return 1;
	numBytes = recvfrom(fd, resp, BUF_SIZE, 0, NULL, NULL);
	if (numBytes == -1)
			return 1;
	else
		printf("Response : %s\n", resp);
    
    close(fd);          // Đóng socket
	remove(SOCK_PATH);  // Xóa file socket
    printf("\nClose and remove Socket!\n");

    return 0;
}