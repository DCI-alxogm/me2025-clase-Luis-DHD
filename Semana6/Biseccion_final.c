#include <stdio.h>
#include <math.h>
#include <stdlib.h>
float f(float c) {
    return 9.8*68.1/c*(1-exp(-c*10/68.1))-40;
}

int main() {
    float a, b, k, k_old, f_a, f_b, f_k;
    float E_max, error;
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
    printf("\nIteracion\t a\t\t k\t\t b\t\t f(k)\t\t Error\n");
    printf("-------------------------------------------------------------------------------------------\n");
    
    k = (a + b) / 2;
    f_k = f(k);
    error = 100; 
    
    printf("%d\t\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\n", iter, a, k, b, f_k, error);
    
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
        error = fabs((k - k_old) / k) * 100;
        printf("%d\t\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\n", iter, a, k, b, f_k, error);
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("\nRaiz aproximada: %.6f\n", k);
    printf("Error final: %.6f%%\n", error);
    printf("Numero de iteraciones: %d\n", iter);
    
    return 0;
}
