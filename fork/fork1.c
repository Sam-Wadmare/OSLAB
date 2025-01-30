#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    fork();
    fork();
    fork();
    printf("hello\n");    
    return 0;
}