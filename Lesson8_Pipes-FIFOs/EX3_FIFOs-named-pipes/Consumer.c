#include <stdio.h>
#include <string.h>
#include <fcntl.h>      // Cung cấp các định nghĩa và hàm chuẩn để điều khiển và quản lý file
#include <sys/stat.h>   // Chứa các hàm hoặc thao tác liên quan đến thuộc tính của file
#include <sys/types.h>  // Chứa các định nghĩa kiểu dữ liệu đặc biệt
#include <unistd.h>     // Cung cấp các hàm trong hệ thống POSIX (read, write, open, close...)

// FIFO file path
#define FIFO_FILE   "./Astatine_FIFOs"
#define BUFF_SIZE   1024

int main(int argc, char const *argv[])
{   
    char buff[BUFF_SIZE];
    int fd;

    // mkfifo(<pathname>, <permission>)
    mkfifo(FIFO_FILE, 0666);

    while (1) {
        // Read first
        fd = open(FIFO_FILE, O_RDONLY);
        read(fd, buff, BUFF_SIZE);

        printf("producer message: %s", buff);
        close(fd);

        // Write first
        printf("Message to producer: "); fflush(stdin);       
        fgets(buff, BUFF_SIZE, stdin);

        fd = open(FIFO_FILE, O_WRONLY);
        write(fd, buff, strlen(buff) +1);
        close(fd);
    }

    return 0;
}