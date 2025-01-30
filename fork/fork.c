#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    pid_t pid;
    pid = fork();
    if (pid < 0){
        perror("Fork Fail");
        return 1;
    }
    else if (pid == 0){
        //child process
        printf("Child Process: PID= %d\n",getpid());
        //it performs child specific tasks here
    }
    else {
        //Parent Process
        printf("Parent Process: PID = %d, Child-PID = %d\n",getpid(),pid);
        //it performs parent specific tasks here
    }
    return 0;
}