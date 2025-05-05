#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void main() {
    pid_t pid;
    // Tiến trình cha in ra PID
    printf("Parent process: My PID is %d\n", getpid());

    //Tạo ra child process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return;
    } else if (pid == 0) {
        // Tiến trình con
        printf("Child process: My PID is %d\n", getpid());
    } else {
        // Tiến trình cha
        printf("Parent process: My child's PID is %d\n", pid);
    }

}