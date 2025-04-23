//Bounded buffer problem using POSIX threads 
#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#define BUFFER_SIZE 5 
#define NUM_ITEMS 10 // Number of items to produce/consume 
// Shared buffer 
int buffer[BUFFER_SIZE]; 
int in = 0; // Index where the producer will insert the next item 
int out = 0; // Index where the consumer will remove the next item 
// Semaphores and mutex 
sem_t empty; 
sem_t full; 
pthread_mutex_t mutex; 
// Producer thread function 
void *producer(void *arg) { 
for (int i = 0; i < NUM_ITEMS; i++) { 
        int item = rand() % 100; // Produce a random item 
 // Wait for space in the buffer 
        sem_wait(&empty); 
// Lock the buffer to safely add the item 
        pthread_mutex_lock(&mutex); 
 
        // Add the item to the buffer 
        buffer[in] = item; 
        in = (in + 1) % BUFFER_SIZE; 
        printf("Produced: %d\n", item); 
 
        // Unlock the buffer 
        pthread_mutex_unlock(&mutex); 
 
        // Signal that there is a new item in the buffer 
        sem_post(&full); 
 
        // Simulate producing time 
        sleep(1); 
    } 
    pthread_exit(NULL); 
} 
// Consumer thread function 
void *consumer(void *arg) { 
    for (int i = 0; i < NUM_ITEMS; i++) { 
        // Wait for an item in the buffer 
        sem_wait(&full); 
 
        // Lock the buffer to safely remove the item 
        pthread_mutex_lock(&mutex); 
 
        // Remove the item from the buffer 
        int item = buffer[out]; 
        out = (out + 1) % BUFFER_SIZE; 
        printf("Consumed: %d\n", item); 
 // Unlock the buffer 
        pthread_mutex_unlock(&mutex); 
 // Signal that there is space in the buffer 
        sem_post(&empty); 
// Simulate consuming time 
        sleep(1); 
    } 
    pthread_exit(NULL); 
} 
int main() { 
    pthread_t prod, cons; 
 
    // Initialize the semaphores and mutex 
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, the buffer is empty 
    sem_init(&full, 0, 0); // Initially, the buffer is full (0 items) 
    pthread_mutex_init(&mutex, NULL); 
 
    // Create the producer and consumer threads 
    pthread_create(&prod, NULL, producer, NULL); 
    pthread_create(&cons, NULL, consumer, NULL); 
// Wait for the threads to finish 
pthread_join(prod, NULL); 
pthread_join(cons, NULL); 
// Clean up resources 
sem_destroy(&empty); 
sem_destroy(&full); 
pthread_mutex_destroy(&mutex); 
return 0; 
}
