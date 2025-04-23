#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

int shared = 1;     // Shared variable
sem_t s;            // Semaphore variable

void* fun1() {
    int x;
    sem_wait(&s);   // Lock (enter critical section)

    x = shared;
    printf("Thread 1 reads shared = %d\n", x);
    x++;
    printf("Thread 1 increments to %d\n", x);
    sleep(1);       // Simulate delay
    shared = x;
    printf("Thread 1 updates shared to %d\n", shared);

    sem_post(&s);   // Unlock (exit critical section)
    return NULL;
}

void* fun2() {
    int y;
    sem_wait(&s);   // Lock

    y = shared;
    printf("Thread 2 reads shared = %d\n", y);
    y--;
    printf("Thread 2 decrements to %d\n", y);
    sleep(1);       // Simulate delay
    shared = y;
    printf("Thread 2 updates shared to %d\n", shared);

    sem_post(&s);   // Unlock
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    sem_init(&s, 0, 1);  // Initialize semaphore with 1 (binary semaphore)

    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of shared = %d\n", shared);
    return 0;
}
