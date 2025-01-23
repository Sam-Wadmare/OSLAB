#include<unistd.h>
int main() {
   char buff[20];
   
   read(0,buff,7);
   
   write(1,buff,7);
   return 0;
   
  
   
}
