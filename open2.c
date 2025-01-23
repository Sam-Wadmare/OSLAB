#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main() {
int n,f,f1;
char buff[10];

f=open("file is opening",O_RDWR);
f1=lseek(f,10,SEEK_SET);
printf("pointer is at %d",f1);

read(f,buff,10);

write(1,buff,10);

//lseek(f,6,SEEK_CUR);

read(f,buff,10);

write(1,buff,10);

return 0;

}
