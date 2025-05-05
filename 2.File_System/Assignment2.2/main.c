#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "cách dùng: %s filename num-bytes [r/w] \"content\"\n", argv[0]);
        return ;
    }

    char *filename = argv[1];
    int num_bytes = atoi(argv[2]);
    char mode = argv[3][0];
    char *content = argv[4];

    if (mode == 'r') {
        int fd = open(filename, O_RDONLY);
        if (fd < 0) {
            perror("Error opening file for reading");
            return ;
        }

        char *buffer = (char *)malloc(num_bytes + 1);
        if (!buffer) {
            perror("Memory allocation failed");
            close(fd);
            return ;
        }

        ssize_t bytes_read = read(fd, buffer, num_bytes);
        if (bytes_read < 0) {
            perror("Error reading file");
            free(buffer);
            close(fd);
            return ;
        }

        buffer[bytes_read] = '\0';
        printf("Read content: %s\n", buffer);

        free(buffer);
        close(fd);
    } else if (mode == 'w') {
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            perror("Error opening file for writing");
            return ;
        }

        ssize_t bytes_written = write(fd, content, num_bytes);
        if (bytes_written < 0) {
            perror("Error writing to file");
            close(fd);
            return ;
        }

        printf("Written %ld bytes to the file.\n", bytes_written);
        close(fd);
    } else {
        fprintf(stderr, "Invalid mode. Use 'r' for read or 'w' for write.\n");
        return ;
    }

    
}