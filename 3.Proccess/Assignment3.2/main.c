#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();
    int status, retVal;

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child process
        char *env_var = getenv("ACTION");
        if (env_var == NULL) {
            fprintf(stderr, "Environment variable ACTION is not set.\n");
            exit(1);
        }

        if (env_var[0] == '1') {
            // Execute "ls"
            char *args[] = {"ls", "-l", NULL};
            execvp("ls", args);
        } else if (env_var[0] == '2') {
            // Execute "date"
            char *args[] = {"date", NULL};
            execvp("date", args);
        } else {
            fprintf(stderr, "Invalid ACTION value. Use 1 for ls or 2 for date.\n");
            exit(1);
        }

        // If execvp fails
        perror("execvp failed");
        exit(1);
    } else { // Parent process
        printf("Parent process\n");

        // retVal = wait(&status); // Wait for the child process to finish
        // printf("Child process has finished execution.\n PID: %d \n", retVal);
        // if(status == -1){
        //     printf("wait unsuccessful");
        // }
        // if(WIFEXITED(status) == 1){
        //     printf("Normally termination, status = %d\n", WEXITSTATUS(status));
        // }
        // else{
        //     printf("Abnormally termination, status = %d\n", WTERMSIG(status));
        // }
    }
    return 0;
}