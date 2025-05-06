#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ARRAY_SIZE 100

int numbers[ARRAY_SIZE];
int even_count = 0;
int odd_count = 0;

void* count_even(void* arg) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (numbers[i] % 2 == 0) {
            even_count++;
        }
    }
    return NULL;
}

void* count_odd(void* arg) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (numbers[i] % 2 != 0) {
            odd_count++;
        }
    }
    return NULL;
}

int main() {
    pthread_t even_thread, odd_thread;

    // Seed the random number generator
    srand(time(NULL));

    // Generate random numbers between 1 and 100
    for (int i = 0; i < ARRAY_SIZE; i++) {
        numbers[i] = rand() % 100 + 1;
    }

    // Create threads
    pthread_create(&even_thread, NULL, count_even, NULL);
    pthread_create(&odd_thread, NULL, count_odd, NULL);

    // Wait for threads to finish
    pthread_join(even_thread, NULL);
    pthread_join(odd_thread, NULL);

    // Print results
    printf("Total even numbers: %d\n", even_count);
    printf("Total odd numbers: %d\n", odd_count);

    return 0;
}