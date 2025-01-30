#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int n, fd;
    char buffer[10];

    fd = open("hi.txt", O_RDONLY);
    lseek(fd, -6, SEEK_END);  
    n = read(fd, buffer, 5);
    write(1, buffer, n);  

    return 0;
}
