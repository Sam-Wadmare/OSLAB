#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int shared = 1; // Shared variable

void* fun1() {
    int x = shared;
    printf("Thread 1 reads shared = %d\n", x);
    x++; // Increment locally
    printf("Thread 1 increments to %d\n", x);
    sleep(1); // Simulates delay
    shared = x;
    printf("Thread 1 updates shared to %d\n", shared);
    return NULL;
}

void* fun2() {
    int y = shared;
    printf("Thread 2 reads shared = %d\n", y);
    y--; // Decrement locally
    printf("Thread 2 decrements to %d\n", y);
    sleep(1); // Simulates delay
    shared = y;
    printf("Thread 2 updates shared to %d\n", shared);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Create threads
    pthread_create(&t1, NULL, fun1, NULL);
    pthread_create(&t2, NULL, fun2, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final value of shared = %d\n", shared);
    return 0;
}
