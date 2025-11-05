// Optimización 2D - Búsqueda Aleatoria
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>

double f(double x, double y) {
    return y - x - 2*x*x - 2*x*y - y*y;
}

double random(double min, double max) {
    return min + (max - min) * ((double)rand() / RAND_MAX);
}

int main() {
    double a_x, b_x, a_y, b_y;
    int n_iter;

    printf("Limite inferior (x): "); scanf("%lf", &a_x);
    printf("Limite superior (x): "); scanf("%lf", &b_x);
    printf("Limite inferior (y): "); scanf("%lf", &a_y);
    printf("Limite superior (y): "); scanf("%lf", &b_y);
    printf("Numero de iteraciones: "); scanf("%d", &n_iter);

    if (n_iter <= 0) {
        printf("Error: número de iteraciones debe ser positivo.\n");
        return 1;
    }

    srand(time(NULL)); // Inicializar semilla

    double best_x = random(a_x, b_x);
    double best_y = random(a_y, b_y);
    double best_f = f(best_x, best_y);

    for (int i = 0; i < n_iter; i++) {
        double x = random(a_x, b_x);
        double y = random(a_y, b_y);
        double fnc = f(x, y);

        if (fnc > best_f) {
            best_f = fnc;
            best_x = x;
            best_y = y;
        }
    }

    printf("\n Resultados \n");
    printf("N. de iteraciones: %d\n", n_iter);
    printf("Maximo encontrado en:\n");
    printf("  x = %.6f\n", best_x);
    printf("  y = %.6f\n", best_y);
    printf("  f(x, y) = %.6f\n", best_f);

    return 0;
}