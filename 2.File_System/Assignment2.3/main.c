#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

void main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return;
    }
    const char *filename = argv[1];
    // Lấy thông tin file
    struct stat fileStat;
    if (stat(filename, &fileStat) < 0) {
        perror("Error getting file information");
        return;
    }    
    // Lấy thông tin chi tiết từ fileStat
    printf("File Name: %s\n", filename);

    // Xác định loại file
    printf("File Type: ");
    if (S_ISREG(fileStat.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(fileStat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(fileStat.st_mode)) {
        printf("Symbolic Link\n");
    } else {
        printf("Other\n");
    }

    // Lấy thời gian chỉnh sửa cuối cùng
    char timeBuffer[26];
    struct tm *tm_info = localtime(&fileStat.st_mtime);
    strftime(timeBuffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Last Modified Time: %s\n", timeBuffer);
    printf("File Size: %ld bytes\n", fileStat.st_size);
}