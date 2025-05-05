#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) is running.\n", getpid());
        sleep(10);
        exit(1);//kết thúc trước khi tiến trình cha kết thúc và rơi vào trạng thái zombie
    } else {
        // Parent process
        printf("Parent process (PID: %d) created a child (PID: %d).\n", getpid(), pid);
        printf("Parent process is exiting.\n");
        while(1);
    }
}