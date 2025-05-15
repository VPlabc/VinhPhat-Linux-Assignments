#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to be executed by each thread
void* print_message(void* thread_id) {
    long tid = (long)thread_id;
    printf("Thread %ld: Hello from thread\n", tid);
    pthread_exit(NULL); // Exit the thread
}

int main() {
    pthread_t threads[2]; // Array to hold thread IDs
    int rc;
    long t;

    // Create two threads
    for (t = 0; t < 2; t++) {
        printf("Main: Creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_message, (void*)t);
        if (rc) {
            printf("Error: Unable to create thread %d\n", rc);
            exit(-1);
        }
    }

    // Wait for both threads to complete
    for (t = 0; t < 2; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("Main: All threads completed. Exiting program.\n");
    return 0;
}