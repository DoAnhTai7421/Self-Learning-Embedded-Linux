#include <sys/un.h>     // cung cấp các cấu trúc và hàm để làm việc với Unix Domain Socket
#include <sys/socket.h> // Cung cấp các API cơ bản cho lập trình socket: socket(), bind(), listen(), accept()...
#include <stddef.h>     // Cung cấp các định nghĩa chuẩn
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define BUF_SIZE 10     // Kích thước của bộ đệm để lưu trữ dữ liệu gửi/nhận là 10 byte
#define SOCK_PATH "./sock_stream"   // Định nghĩa đường dẫn đến socket miền Unix

int fd, datafd;

void sig_handler1(int num){
    close(fd);          // Đóng socket
	remove(SOCK_PATH);  // Xóa file socket
    printf("\nClose and remove Socket!\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr;
    
    ssize_t numBytes;               // Lưu số byte thật sự được đọc hoặc ghi vào socket
    socklen_t len;                  // Lưu kích thước của địa chỉ socket
    char buf[BUF_SIZE]={0};         // Lưu trữ dữ liệu được đọc hoặc ghi vào socket, khởi tạo các phần tử = 0

    fd = socket(AF_UNIX, SOCK_STREAM, 0);   // Tạo socket
    if (fd == -1)                           // Kiểm tra lỗi khi tạo socket
        return 1;

    memset(&svaddr, 0, sizeof(struct sockaddr_un));                     // Khởi tạo địa chỉ server Unix stream socket
    svaddr.sun_family = AF_UNIX;                                        // Gán loại miền của địa chỉ là Unix
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path)-1);     // Sao chép đường dẫn của socket (SOCK_PATH) vào trường .sun_path của svaddr

    if (bind(fd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_un)) == -1)    // gắn socket vào địa chỉ server và kiểm tra lỗi
        return 1;
 
    if ((listen(fd, 5)) == -1)                  // Đặt socket ở chế độ nghe, cho phép server nhận kết nối từ client
	    return 1; 
    else
	    printf("start listening on server\n");
	
    if((datafd = accept(fd, (struct sockaddr*)&svaddr, &len)) == -1)    // Chấp nhận kết nối từ client và lưu dữ liệu vào datafd
	    return 1;
    else
	    printf("accept connect\n");
	
    while(1) {
        if(read(datafd, buf, BUF_SIZE) > 0)                 // Đọc dữ liệu socket từ datafd vào buf sau đó trả về số byte thật sự đọc được
		{
			for (int j = 0; j < BUF_SIZE; j++) 
				buf[j] = toupper((unsigned char) buf[j]);   // Chuyển dữ liệu thành kiểu in hoa
			printf("start response %s\n", buf);             // In thông báo
			write(datafd, buf, BUF_SIZE-1);                 // Gửi phản hồi lại cho client
		}
        if(signal(SIGINT, sig_handler1) == SIG_ERR){
            fprintf(stderr, "Cannot handle SIGINT\n");
            exit(EXIT_FAILURE);
        }
    }
}