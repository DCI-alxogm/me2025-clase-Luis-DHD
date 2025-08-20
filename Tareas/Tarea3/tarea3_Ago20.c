#include <stdio.h>
#include <math.h>

int main() {
    float x;
    printf("Ingrese el valor de x: ");
    scanf("%f", &x);
    float term = 1.0;     
    float sum_f = term;
    float sum_0;
    float error;
    int n;
    printf("n\t aproximación\t error\n");
    printf("------------------------------------------------------\n");
    printf("%3d\t %.4f \t %.4f%%\n", 0, sum_f, 0.0);
    for (n=1; ; n++) {
        sum_0 = sum_f;
        term = term * x / n;
        sum_f += term;
        error = fabs((sum_f - sum_0)/sum_f*100);
        printf("%3d \t %.4f \t %.4f%%\n", n, sum_f, error);
        if (error < 0.1) {
            break;
        }
    }

    printf("------------------------------------------------------\n");
    printf("n final= %d\n", n);
    printf("Aproximación final: %.5f\n", sum_f);

    return 0;
}