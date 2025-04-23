#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
 
#define NUM_PHILOSOPHERS 5 
 
// Semaphore for each chopstick 
sem_t chopstick[NUM_PHILOSOPHERS]; 
 
// Semaphore to limit the number of philosophers who may sit at the table 
sem_t room; 
 
// Philosopher thread function 
void *philosopher(void *num) { 
    int id = *(int *)num; 
 
    while (1) { 
        // Thinking 
        printf("Philosopher %d is thinking.\n", id); 
        sleep(rand() % 3 + 1); 
 
        // Request permission to enter dining room 
        sem_wait(&room); 
 
        // Pick up left chopstick 
        sem_wait(&chopstick[id]); 
        printf("Philosopher %d picked up left chopstick %d.\n", id, id); 
 
        // Pick up right chopstick 
        sem_wait(&chopstick[(id + 1) % NUM_PHILOSOPHERS]); 
        printf("Philosopher %d picked up right chopstick %d.\n", id, (id + 1) % 
NUM_PHILOSOPHERS); 
 
        // Eating 
        printf("Philosopher %d is eating.\n", id); 
        sleep(rand() % 2 + 1); 
 
        // Put down right chopstick 
        sem_post(&chopstick[(id + 1) % NUM_PHILOSOPHERS]); 
        printf("Philosopher %d put down right chopstick %d.\n", id, (id + 1) % 
NUM_PHILOSOPHERS); 
 
        // Put down left chopstick 
        sem_post(&chopstick[id]); 
        printf("Philosopher %d put down left chopstick %d.\n", id, id); 
 
        // Leave dining room 
        sem_post(&room); 
    } 
 
    pthread_exit(NULL); 
} 
 
int main() { 
    pthread_t philosophers[NUM_PHILOSOPHERS]; 
    int ids[NUM_PHILOSOPHERS]; 
 
    // Initialize semaphores 
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) { 
        sem_init(&chopstick[i], 0, 1); 
    } 
    sem_init(&room, 0, NUM_PHILOSOPHERS - 1); // Only 4 philosophers can try to eat at a 
time 
 
    // Create philosopher threads 
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) { 
        ids[i] = i; 
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]); 
    } 
 
    // Wait for threads (not necessary in an infinite loop but good practice) 
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) { 
        pthread_join(philosophers[i], NULL); 
    } 
 
    // Destroy semaphores (not reached, since the loop is infinite) 
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) { 
        sem_destroy(&chopstick[i]); 
    } 
    sem_destroy(&room); 
 return 0; 
}
