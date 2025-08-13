#include <stdio.h>
#include<math.h>

int main(){
  int a=3;
  int b=4;
  int c= 5;
  int d= 7;
    printf("e=(a+b)*c/d= %d\n e=((a+b)*c)/d= %d\n e= a+b*c/d= %d\n e=a+(b*c)/d= %d", (a+b)*c/d, ((a+b)*c)/d, a+b*c/d, a+(b*c)/d );
  return 0;
}