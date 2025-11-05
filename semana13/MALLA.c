// Optimización 2D - Método de Malla (Grid Search) con límite de iteraciones
#include <stdio.h>
#include <math.h>
#include <float.h>

double f(double x, double y) {
    return y - x - 2*x*x - 2*x*y - y*y;
}

int main() {
    double a_x, b_x, a_y, b_y, grid;
    int iter_max;

    printf("Introduzca el limite inferior (x): "); scanf("%lf", &a_x);
    printf("Introduzca el limite superior (x): "); scanf("%lf", &b_x);
    printf("Introduzca el limite inferior (y): "); scanf("%lf", &a_y);
    printf("Introduzca el limite superior (y): "); scanf("%lf", &b_y);
    printf("Introduzca el espaciado (grid): "); scanf("%lf", &grid);
    printf("Introduzca el numero maximo de iteraciones: "); scanf("%d", &iter_max); 

    if (grid <= 0 || iter_max <= 0) {
        printf("Error: el espaciado y el número de iteraciones deben ser positivos.\n");
        return 1;
    }

    double best_x = a_x;
    double best_y = a_y;
    double best_f = f(a_x, a_y);
    int iter = 0;
    int stop = 0; 

    for (double x = a_x; x <= b_x && !stop; x += grid) {
        for (double y = a_y; y <= b_y && !stop; y += grid) {
            if (iter >= iter_max) {
                stop = 1;
                break;
            }

            double fnc = f(x, y);
            iter++;

            if (fnc > best_f) {
                best_f = fnc;
                best_x = x;
                best_y = y;
            }
        }
    }

    printf("\n Resultados \n");
    printf("N. de iteraciones: %d\n", iter);
    printf("Maximo encontrado en:\n");
    printf("  x = %.6f\n", best_x);
    printf("  y = %.6f\n", best_y);
    printf("  f(x, y) = %.6f\n", best_f);

    return 0;
}