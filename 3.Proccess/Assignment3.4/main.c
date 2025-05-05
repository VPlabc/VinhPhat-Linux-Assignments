#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    int status, retVal;

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process is waiting 3s for exit(2) signal\n");
        sleep(3); // Wait for 3 seconds
        exit(2);
    } else {
        // Parent process
        printf("Parent process wait signal.\n");
        retVal = wait(&status); // Wait for the child process to finish
        printf("Child process has finished execution.\n PID: %d \n", retVal);
        if(status == -1){
            printf("wait unsuccessful");
        }
        if(WIFEXITED(status) == 1){
            printf("Normally termination, status = %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}