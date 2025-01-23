#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main() {

int n,fd;

char buff[50];
fd=open("test.txt",O_RDONLY);// this func opens the test.txt file on read mode

printf("the file discriptor of file is : %d \n ",fd);
n=read(fd,buff,10); //it reads 10 char from file pointed by file discriptor and save it //buffermemory
 write(1,buff,n);//it writes msg from buff mem on display
return 0;
}

