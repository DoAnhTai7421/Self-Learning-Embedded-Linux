#include <sys/un.h>     // cung cấp các cấu trúc và hàm để làm việc với Unix Domain Socket
#include <sys/socket.h> // Cung cấp các API cơ bản cho lập trình socket: socket(), bind(), listen(), accept()...
#include <stddef.h>     // Cung cấp các định nghĩa chuẩn
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define BUF_SIZE 10
#define SOCK_PATH "./sock_dgram"

int fd;

void sig_handler(int num){
    close(fd);          // Đóng socket
	remove(SOCK_PATH);  // Xóa file socket
    printf("\nClose and remove Socket!\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr, claddr;
    int j;
    ssize_t numBytes;
    socklen_t len;
    char buf[BUF_SIZE];

    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd == -1) 
        return 1;

    memset(&svaddr, 0, sizeof(struct sockaddr_un)); 
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path)-1);

    if (bind(fd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) == -1) 
        return 1; 
    printf("start listening on server\n");
	
    while(1) {
        len = sizeof(struct sockaddr_un);
        numBytes = recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);
		if (numBytes == -1)
			return 1;
			
		if (claddr.sun_path[0] != '\0') {
            printf("Server received %ld bytes from %s\n", (long)numBytes, claddr.sun_path);
        } else {
            printf("Server received %ld bytes from an unnamed client\n", (long)numBytes);
        }

		for (j = 0; j < numBytes; j++) 
			buf[j] = toupper((unsigned char) buf[j]);
			
		if (sendto(fd, buf, numBytes, 0, (struct sockaddr *) &claddr, len) != numBytes) 
			printf("sendto error\n");
        
        if(signal(SIGINT, sig_handler) == SIG_ERR){
            fprintf(stderr, "Cannot handle SIGINT\n");
            exit(EXIT_FAILURE);
        }
	}
}