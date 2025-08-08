/* hacer un programa que imprima 5 números flotantes y el valor de las siguientes funciones:
f(x)= x^2
f(x)= log(x+1)
f(x)= exp(x) + cos(x) */
#include <stdio.h>
#include <math.h>

int main(){
  float num [5]= {3.1, 3.2, 3.3, 3.4, 3.5};
  int tamaño= sizeof(num)/ sizeof(num [0]);
  printf("Los valores del arreglo son:");
   for (int i = 0; i < tamaño; i++) {
    printf("%.2f ", num[i]); 
  }
  printf("\n");
  float x;
  x= 4.2;
  printf("x= %.2f\n x^2= %.2f\n log(x)= %.2f\n exp(x)+cos(x)= %.2f",x, pow(x,2), log10(x), exp(x)+cos(x));
  return 0; 
}