#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void main() {
    pid_t pid;
    printf("Parent process: My PID is %d\n", getpid());

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return;
    } else if (pid == 0) {
        // Child process
        printf("Child process: My PID is %d\n", getpid());
    } else {
        // Parent process
        printf("Parent process: My child's PID is %d\n", pid);
    }

}