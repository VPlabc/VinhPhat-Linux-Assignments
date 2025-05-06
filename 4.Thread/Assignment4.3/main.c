#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ITERATIONS 10

int data = 0; // Global variable to store the data
int ready = 0; // Flag to indicate if data is ready
pthread_mutex_t mutex;
pthread_cond_t cond;

void* producer(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);

        // Produce a random number between 1 and 10
        data = rand() % 10 + 1;
        printf("Producer: Produced data = %d\n", data);

        ready = 1; // Mark data as ready
        pthread_cond_signal(&cond); // Signal the consumer
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate some delay
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);

        while (!ready) {
            pthread_cond_wait(&cond, &mutex); // Wait for the producer's signal
        }

        // Consume the data
        printf("Consumer: Consumed data = %d\n", data);
        ready = 0; // Mark data as consumed

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize mutex and condition variable
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Destroy mutex and condition variable
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}