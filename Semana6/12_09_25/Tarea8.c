#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//float f(float x) {
    //return sin(10*x)-cos(3*x);
//float f(float c) {
    //return 9.81*68.1/c*(1-exp(-c/68.1*10))-40;
    float f(float x) {
    return pow(x,10)-1;
}
int main() {
    float a, b, k, k_old, f_a, f_b, f_k,dif_x;
    float E_max, error,error_aprox,e_a;
    int iter = 0;
    int max_iter = 100;
    
    printf("Ingrese el limite inferior: "); scanf("%f", &a);
    printf("Ingrese el limite superior: "); scanf("%f", &b);
    printf("Ingrese el error maximo: "); scanf("%f", &E_max);
    
    f_a = f(a);
    f_b = f(b);
    
    if (f_a * f_b >= 0) {
        printf("\n*** ERROR ***\n");
        printf("No se cumple el criterio f(a)*f(b) < 0\n");
        printf("Elija otro intervalo\n");
        return 1;
    }
    printf("\nIteracion\t a\t\t k\t\t b\t\t f(k)\t Error (rel) \tError (aprox)\t Error(calc)\n");
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    
    k = (a + b) / 2;
    f_k = f(k);
    error = INFINITY; 
    error_aprox=INFINITY;
    e_a=INFINITY;
    if (f(a) * f(k) < 0) {
            b = k; 
        } else {
            a = k; 
        }
    dif_x=fabs(b-a);
    printf("%d\t\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t\t%.6f\t\t%.6f\n", iter, a, k, b, f_k, error, error_aprox, e_a);
    
    while (error > E_max && iter < max_iter) {
        iter++;
        k_old = k;
        if (f(a) * f(k) < 0) {
            b = k; 
        } else {
            a = k; 
        }
        k = (a + b) / 2;
        f_k = f(k);
        e_a=dif_x/pow(2,iter);
        error_aprox= fabs(k-k_old);
        error = error_aprox / k;
        printf("%d\t\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t\n", iter, a, k, b, f_k, error, error_aprox,e_a);
    }
    printf("----------------------------------------------------------------------------------------------------------------------------\n");
    printf("\nRaiz aproximada: %.6f\n", k);
    printf("Error final: %.6f\n", error);
    printf("Numero de iteraciones: %d\n", iter);
    
    return 0;
}