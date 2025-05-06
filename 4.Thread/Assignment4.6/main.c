#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 1000000
#define NUM_THREADS 4

int array[ARRAY_SIZE];
long long global_sum = 0;
pthread_mutex_t mutex;

void* partial_sum(void* arg) {
    int thread_part = *(int*)arg;
    long long local_sum = 0;

    int start = thread_part * (ARRAY_SIZE / NUM_THREADS);
    int end = (thread_part + 1) * (ARRAY_SIZE / NUM_THREADS);

    for (int i = start; i < end; i++) {
        local_sum += array[i];
    }
    printf("Thread %d partial sum: %lld\n", thread_part, local_sum);
    pthread_mutex_lock(&mutex);
    global_sum += local_sum;
    pthread_mutex_unlock(&mutex);

    free(arg);
    return NULL;
}

int main() {
    // Initialize the array with values
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 1; // Assigning 1 for simplicity, so the sum should be ARRAY_SIZE
    }

    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        int* thread_part = malloc(sizeof(int));
        *thread_part = i;
        if (pthread_create(&threads[i], NULL, partial_sum, thread_part) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Total sum of the array: %lld\n", global_sum);
    return 0;
}