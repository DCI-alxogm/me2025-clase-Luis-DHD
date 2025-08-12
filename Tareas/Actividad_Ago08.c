#include <stdio.h>
#include<math.h>

int main(){
  float x[5]={1.1,1.2,1.3,1.4,1.5};
  int tamaño= sizeof(x)/sizeof(x[0]);
  printf("x\t  x^2\t  log(x+1)\t  exp(x)+cos(x)\n");
  for (int i=0; i<tamaño; i++){
  printf(" %f %f %f %f\n ", x[i], pow(x[i],2), log10(x[i]+1), exp(x[i])+cos(x[i]));
  }
  return 0;
}