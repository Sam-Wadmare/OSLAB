#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* thread1_func(void* arg) {
    FILE *file=fopen("thread.txt","w");
    if(file == NULL ){
        perror("Error in opeing a file");
        return NULL;
    }
    printf("Thread t1: File created successfully");
    fclose(file);
    return NULL;
}
void* thread2_func(void* arg) {
    FILE *file=fopen("thread.txt","a");
    if (file == NULL) {
         perror("Error in opeing a file");
        return NULL;
    }
    fprintf(file,"HEllo this is thread t2");
    printf("Text writtten in file successfully");
    fclose(file);
    return NULL;
}

int main() {
    
    pthread_t t1,t2;
    
    if(pthread_create(&t1,NULL,thread1_func,NULL)!=0) {
        perror("Error while crrating theread t1");
        return 1;
    }
    if(pthread_create(&t2,NULL,thread2_func,NULL)!=0) {
        perror("Error while crrating theread t2");
        return 1;
    }
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    
    printf("both thread finished executing");
    return 0;
}
