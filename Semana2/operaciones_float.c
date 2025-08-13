#include <stdio.h>
#include<math.h>

int main(){
  float a=3;
  float b=4;
  float c= 5;
  float d= 7;
    printf("e=(a+b)*c/d= %.2f\n e=((a+b)*c)/d= %.2f\n e= a+b*c/d= %.2f\n e=a+(b*c)/d= %.2f", (a+b)*c/d, ((a+b)*c)/d, a+b*c/d, a+(b*c)/d );
  return 0;
}