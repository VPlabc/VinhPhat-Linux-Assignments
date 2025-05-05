#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void handle_sigusr1(int sig) {
    printf("Child process received SIGUSR1 signal.\n");
    exit(1);
}

int main() {
    pid_t pid = fork();
    int status, retVal;

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process.\n");
        signal(SIGUSR1, handle_sigusr1);
        printf("Child process is waiting for SIGUSR1 signal...\n");
        while (1);
    } else {
        // Parent process
        printf("Parent process.\n");
        sleep(2); // Wait for 2 seconds
        printf("Parent process sending SIGUSR1 to child process.\n");
        kill(pid, SIGUSR1);
        retVal = wait(&status); // Wait for the child process to finish
        printf("Child process has finished execution.\n PID: %d \n", retVal);
        if(status == -1){
            printf("wait unsuccessful");
        }
    }

    return 0;
}