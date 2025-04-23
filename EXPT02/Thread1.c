#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
int i,j;
void* thread_func(void* arg) {
    
    printf("Inside the threrad: ");
    for(i=0;i<=5;i++){
        printf("Thread: %d \n ",i);
        sleep(2);
    }
    return NULL;
}
int  main() {
    pthread_t thread;
    
    pthread_create(&thread,NULL,thread_func,NULL);
    pthread_join(thread,NULL);
    
    printf("\n inside Main : ");
    for(j=10;j<=15;j++) {
        printf("Thread: %d \n ",j);
        sleep(3);
    }
    return 0;
}
