#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Shared data and read-write lock
int data = 0;
pthread_rwlock_t rwlock;

// Reader thread function
void* reader_thread(void* arg) {
    int thread_id = *(int*)arg;
    for (int i = 0; i < 5; i++) { // Each reader reads 5 times
        pthread_rwlock_rdlock(&rwlock);
        printf("Reader %d: Read data = %d\n", thread_id, data);
        pthread_rwlock_unlock(&rwlock);
        usleep(100000); // Simulate some delay
    }
    return NULL;
}

// Writer thread function
void* writer_thread(void* arg) {
    int thread_id = *(int*)arg;
    for (int i = 0; i < 5; i++) { // Each writer writes 5 times
        pthread_rwlock_wrlock(&rwlock);
        data++;
        printf("Writer %d: Incremented data to %d\n", thread_id, data);
        pthread_rwlock_unlock(&rwlock);
        usleep(150000); // Simulate some delay
    }
    return NULL;
}

int main() {
    pthread_t readers[5], writers[2];
    int thread_ids[5 + 2];

    // Initialize the read-write lock
    pthread_rwlock_init(&rwlock, NULL);

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader_thread, &thread_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        thread_ids[5 + i] = i + 1;
        pthread_create(&writers[i], NULL, writer_thread, &thread_ids[5 + i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy the read-write lock
    pthread_rwlock_destroy(&rwlock);

    // Print final value of data
    printf("Final value of data: %d\n", data);

    return 0;
}