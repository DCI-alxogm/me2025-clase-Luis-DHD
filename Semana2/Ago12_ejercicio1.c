#include <stdio.h>
#include<math.h>

int main(){
  int x[5]={1,2,3,4,5};
  int tamaño= sizeof(x)/sizeof(x[0]);
  float results[5];
  for (int i=0; i<tamaño; i++){
  //printf("%d %d\n", x[i], x[i]%2);
  if(x[i]%2==0){
  results[i]=log10(x[i]+1);
  printf("x= %i\n log10(x+1)=%.2f\n ", x[i], results[i]);
  }
  else{
    results[i]=exp(x[i])+cos(x[i]);
    printf("x= %i\n exp(x)+cos(x)=%.2f\n", x[i], results[i]);
  }
  }
  float pi=3.1415926536;
  printf("Pi + Pi= %.16lf", pi+pi);
  return 0;
}