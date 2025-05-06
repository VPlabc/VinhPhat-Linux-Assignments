#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3
#define INCREMENT_COUNT 1000000

// Global counter and mutex
int counter = 0;
pthread_mutex_t counter_mutex;

// Thread function
void* increment_counter(void* arg) {
    pthread_mutex_lock(&counter_mutex); // Lock the mutex
    for (int i = 0; i < INCREMENT_COUNT; i++) {
        counter++; // Safely increment the counter
    }
    pthread_mutex_unlock(&counter_mutex); // Unlock the mutex
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the mutex
    pthread_mutex_init(&counter_mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&counter_mutex);

    // Print the final value of counter
    printf("Target value of counter: %d\n", NUM_THREADS * INCREMENT_COUNT);
    printf("Final value of counter: %d\n", counter);

    return 0;
}