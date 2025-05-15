#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) started.\n", getpid());  
        // thời gian chờ để mô tả tiên trình orphan
        sleep(2);

        printf("Child process (PID: %d) run.\n", getpid());
        while(1);
    } else {
        // Parent process
        printf("Parent process (PID: %d) started.\n", getpid());
        sleep(10);
        printf("Parent process (PID: %d) exiting to create orphan.\n", getpid());
        exit(0);
    }
    
    return 0;
}