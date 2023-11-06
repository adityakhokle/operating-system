#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct {
    int buff[20]; // Shared buffer to store items
    sem_t full, empty; // Semaphores to control access to the buffer
} shared;

shared sh; // Shared data structure
int item; // Item to be produced or consumed
int in = 0, out = 0; // Pointers to track the position in the buffer
pthread_mutex_t mutex; // Mutex for thread synchronization

void *producer() {
    int k = 0;
    while (k < 5) {
        item = rand() % 100; // Generate a random item
        sem_wait(&sh.empty); // Wait if the buffer is full
        pthread_mutex_lock(&mutex); // Lock the mutex to access the buffer

        sh.buff[in++] = item; // Place the item in the buffer
        printf("\nproducer item:%d\n", item); // Print the produced item
        pthread_mutex_unlock(&mutex); // Unlock the mutex
        sem_post(&sh.full); // Signal that the buffer is not empty
        sleep(2); // Sleep for 2 seconds
        k++;
    }
    exit(0); // Exit the thread
}

void *consumer() {
    while (1) {
        while (out <= in) {
            sem_wait(&sh.full); // Wait if the buffer is empty
            pthread_mutex_lock(&mutex); // Lock the mutex to access the buffer
            item = sh.buff[out++]; // Get an item from the buffer
            printf("\nconsumer item:%d\n", item); // Print the consumed item
            pthread_mutex_unlock(&mutex); // Unlock the mutex
            sem_post(&sh.empty); // Signal that the buffer is not full
            sleep(2); // Sleep for 2 seconds
        }
    }
}

int main() {
    pthread_t ptid1, ctid1; // Thread identifiers for producer and consumer
    sem_init(&sh.empty, 0, 20); // Initialize the 'empty' semaphore with a count of 20 (buffer size)
    sem_init(&sh.full, 0, 0); // Initialize the 'full' semaphore with a count of 0
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex for thread synchronization

    pthread_create(&ptid1, NULL, producer, NULL); // Create a producer thread
    pthread_create(&ctid1, NULL, consumer, NULL); // Create a consumer thread

    pthread_join(ptid1, NULL); // Wait for the producer thread to finish
    pthread_join(ctid1, NULL); // Wait for the consumer thread to finish

    return 0;
}
