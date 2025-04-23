#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int shared = 1;                   // Shared variable
pthread_mutex_t lock;            // Mutex lock

void* fun1() {
    int x;

    printf("Thread 1 trying to acquire lock...\n");
    pthread_mutex_lock(&lock);  // Lock acquired

    printf("Thread 1 acquired lock\n");
    x = shared;
    printf("Thread 1 reads shared = %d\n", x);
    x++;
    printf("Thread 1 increments to %d\n", x);
    sleep(1);
    shared = x;
    printf("Thread 1 updates shared to %d\n", shared);

    pthread_mutex_unlock(&lock);  // Release lock
    printf("Thread 1 released lock\n");

    return NULL;
}

void* fun2() {
    int y;

    printf("Thread 2 trying to acquire lock...\n");
    pthread_mutex_lock(&lock);  // Lock acquired

    printf("Thread 2 acquired lock\n");
    y = shared;
    printf("Thread 2 reads shared = %d\n", y);
    y--;
    printf("Thread 2 decrements to %d\n", y);
    sleep(1);
    shared = y;
    printf("Thread 2 updates shared to %d\n", shared);

    pthread_mutex_unlock(&lock);  // Release lock
    printf("Thread 2 released lock\n");

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_mutex_init(&lock, NULL);  // Initialize mutex

    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of shared = %d\n", shared);

    pthread_mutex_destroy(&lock);     // Destroy mutex
    return 0;
}
