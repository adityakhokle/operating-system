#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void *writer_thr(int temp);
void *reader_thr(int temp);
pthread_mutex_t mutex;
sem_t wrt;
int readcount = 0, nwt, nrd;

void main() {
    long int i;
    pthread_mutex_init(&mutex, 0); // Initialize a mutex for synchronization
    sem_init(&wrt, 0, 1); // Initialize a semaphore for writers with a count of 1
    pthread_t reader[100], writer[100]; // Arrays to store reader and writer threads
    printf("\n Enter number of readers:");
    scanf("%d", &nrd);
    printf("\n Enter number of writers:");
    scanf("%d", &nwt);

    for (i = 1; i <= nwt; i++) {
        pthread_create(&writer[i], NULL, (void *)writer_thr, (int *)i); // Create writer threads
        pthread_join(writer[i], NULL); // Wait for the writer threads to finish
    }

    for (i = 1; i <= nrd; i++) {
        pthread_create(&reader[i], NULL, (void *)reader_thr, (int *)i); // Create reader threads
        pthread_join(reader[i], NULL); // Wait for the reader threads to finish
    }

    sem_destroy(&wrt); // Destroy the semaphore
    pthread_mutex_destroy(&mutex); // Destroy the mutex
}

void *reader_thr(int temp) {
    printf("\n Reader %d is trying to enter the database for reading.", temp);
    pthread_mutex_lock(&mutex); // Lock the mutex for synchronization
    readcount++;
    if (readcount == 1)
        sem_wait(&wrt); // If it's the first reader, block writers
    pthread_mutex_unlock(&mutex); // Unlock the mutex

    printf("\nReader %d is now reading in the database.", temp);

    pthread_mutex_lock(&mutex); // Lock the mutex
    readcount--;
    if (readcount == 0)
        sem_post(&wrt); // If no readers are left, allow writers
    pthread_mutex_unlock(&mutex); // Unlock the mutex

    printf("\nReader %d has left the database.\n", temp);
    sleep(3); // Simulate reading time
}

void *writer_thr(int temp) {
    printf("\nWriter %d is trying to enter the database for modifying data", temp);
    sem_wait(&wrt); // Block other writers
    printf("\nWriter %d is writing in the database.", temp);
    sleep(3); // Simulate writing time
    printf("\nWriter %d is leaving the database.\n", temp);
    sem_post(&wrt); // Allow other writers
}
