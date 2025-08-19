#include <stdio.h>
#include <math.h>

int main() {
    float a, b, c, discr, x1, x2, real, i;

    printf("Ingrese los valores de a, b y c\n");
    
    printf("a = ");
    scanf("%f", &a);
    
    printf("b = ");
    scanf("%f", &b);
    
    printf("c = ");
    scanf("%f", &c);

    if (a == 0) {
        if (b == 0) {
          printf("La solución es trivial\n");
        } else {
            x1 = -c / b;
            printf("Solución: x = %.3f\n", x1);
        }
    } else {
        discr = b * b - 4 * a * c;

        if (discr > 0) {
            x1 = (-b + sqrt(discr)) / (2 * a);
            x2 = (-b - sqrt(discr)) / (2 * a);
            printf("La ecuación tiene dos raíces reales:\n");
            printf("x1 = %.3f\n", x1);
            printf("x2 = %.3f\n", x2);
        } else if (discr == 0) {
            x1 = -b / (2 * a);
            printf("La ecuación tiene una raíz real doble:\n");
            printf("x = %.3f\n", x1);
        } else {
            real = -b / (2 * a);
            i = sqrt(-discr) / (2 * a);  
            printf("La ecuación tiene raíces complejas conjugadas:\n");
            printf("x1 = %.3f + i%.3f\n", real, i);
            printf("x2 = %.3f - i%.3f\n", real, i);
        }
    }

    return 0;
}