#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEVICE_FILE "/dev/m_device"
#define BUFFER_SIZE 256

void print_commands() {
    printf("=================================================================\n");
    printf("Available commands:\n");
    printf("  W <String>   : Write <String> to %s\n", DEVICE_FILE);
    printf("  R <file>      : Read and display contents of <file>\n");
    printf("  Exit             : Exit the application\n");
    printf("=================================================================\n");

}

void write_to_device(const char *str) {
    FILE *fp = fopen(DEVICE_FILE, "w");
    if (!fp) {
        perror("Failed to open device file");
        return;
    }
    fprintf(fp, "%s\n", str);
    fclose(fp);
    printf("Written to %s: %s\n", DEVICE_FILE, str);
}

void read_from_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Failed to open file");
        return;
    }
    char buffer[BUFFER_SIZE];
    printf("Contents of %s:\n", filename);
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    fclose(fp);
}

void main(int argc, char *argv[]) {
    char input[BUFFER_SIZE];
    print_commands();
    while (1) {
        printf("\n> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;

        if (strncmp(input, "W ", 1) == 0) {
            write_to_device(input + 2);
        } else if (strncmp(input, "R ", 1) == 0) {
            read_from_file(input + 2);
        } else if (strcmp(input, "Exit") == 0) {
            break;
        } else {
            printf("Unknown command.\n");
            print_commands();
        }
    }
}