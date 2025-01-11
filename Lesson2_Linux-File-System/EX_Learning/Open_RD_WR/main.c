#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    // File path to open or create
    int fd;
    const char* file_path ="example.txt";
    const char* data = "Autumn - Astatine\n";
    ssize_t bytes_written;

    // Create or open the file for writing (O_CREAT) and set file permissions
    fd = open(file_path, O_CREAT | O_WRONLY);
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    // Write data to the file
    bytes_written = write(fd, data, strlen(data));
    if(bytes_written == -1)
    {
        perror("write");
        close(fd);
        exit(1);
    }

    printf("Data written to the file: %s ", data);

    // Close the file
    close(fd);

    return 0;
}