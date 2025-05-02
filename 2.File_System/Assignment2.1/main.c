#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    const char *filename = "test.txt";
    const char *data = "Hello, World!\n";
    fd = open(filename, O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Seek về đầu file
    // if (lseek(fd, 0, SEEK_CUR) == -1) {
    //     perror("Error seeking in file");
    //     close(fd);
    //     return 1;
    // }

    // Ghi data vào file test.txt
    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    /* gặp lỗi Error writing to file: Bad file descriptor 
    do cờ O_APPEND chỉ ghi và cuối chuỗi của file tránh tình trạng ghi đè
    dữ liệu hiện có 
    khi sử dụng cờ O_APPEND kèm với O_WRONLY và không cần sử dụng lseek
    */
    printf("Data written successfully.\n");
    close(fd);
    return 0;
}