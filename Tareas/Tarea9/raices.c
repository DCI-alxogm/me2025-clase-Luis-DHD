#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

// Funciones
double f(double x) { return exp(-x) - x; }
double g(double x) { return exp(-x); }
double df(double x) { return -exp(-x) - 1; }
double ddf(double x) { return exp(-x); }

//Imprime valor
void print_valor(double valor, int converge) {
    if (converge) {
        printf("     -      ");
    } else {
        printf("%12.6f", valor);
    }
}

// Imprime error
void print_error(double error, int converge) {
    if (converge) {
        printf("     -      ");
    } else {
        printf("%12.2e", error);
    }
}

int main() {
    double x0, x1, E_max;
    const int max_iter = 100;

    printf("Ingrese el punto inicial x0: "); scanf("%lf", &x0);
    printf("Ingrese el punto x1 (para secante): "); scanf("%lf", &x1);
    printf("Ingrese el error maximo permitido: "); scanf("%lf", &E_max);

    // Variables para cada método
    double pf_xi = x0, pf_x_ip1;
    double nr_xi = x0, nr_x_ip1;
    double sc_x0 = x0, sc_x1 = x1, sc_x_ip1;
    double nrm_xi = x0, nrm_x_ip1;

    double pf_error = DBL_MAX, nr_error = DBL_MAX, sc_error = DBL_MAX, nrm_error = DBL_MAX;
    int pf_conv = 0, nr_conv = 0, sc_conv = 0, nrm_conv = 0;

    // Primera iteración
    pf_x_ip1 = g(pf_xi);
    pf_error = fabs((pf_x_ip1 - pf_xi) / pf_x_ip1);
    pf_xi = pf_x_ip1;

    nr_x_ip1 = nr_xi - f(nr_xi) / df(nr_xi);
    nr_error =fabs((nr_x_ip1 - nr_xi) / nr_x_ip1);
    nr_xi = nr_x_ip1;

    if (fabs(f(sc_x0) - f(sc_x1)) < 1e-15) {
        printf("\nError: f(x0) ≈ f(x1). Método de la secante no aplicable.\n");
        return 1;
    }
    sc_x_ip1 = sc_x1 - f(sc_x1) * (sc_x0 - sc_x1) / (f(sc_x0) - f(sc_x1));
    sc_error =fabs((sc_x_ip1 - sc_x1) / sc_x_ip1);
    sc_x0 = sc_x1;
    sc_x1 = sc_x_ip1;

    double U = f(nrm_xi) / df(nrm_xi);
    double dU = (pow(df(nrm_xi), 2) - f(nrm_xi) * ddf(nrm_xi)) / pow(df(nrm_xi), 2);
    if (fabs(dU) < 1e-15) {
        printf("\nError: derivada modificada cercana a cero en N-R-Modificado.\n");
        return 1;
    }
    nrm_x_ip1 = nrm_xi - U / dU;
    nrm_error =fabs((nrm_x_ip1 - nrm_xi) / nrm_x_ip1);
    nrm_xi = nrm_x_ip1;

    pf_conv = (pf_error <= E_max);
    nr_conv = (nr_error <= E_max);
    sc_conv = (sc_error <= E_max);
    nrm_conv = (nrm_error <= E_max);

    printf("\n");
    printf("Iter |   x_i+1 (p.f.)    Err   |   x_i+1 (N-R)     Err   |   x_i+1 (Sec.)    Err   |   x_i+1 (N-R M)    Err\n");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    int iter = 1;
    printf("%3d  |", iter);
    print_valor(pf_xi, pf_conv); print_error(pf_error, pf_conv); printf(" |");
    print_valor(nr_xi, nr_conv); print_error(nr_error, nr_conv); printf(" |");
    print_valor(sc_x1, sc_conv); print_error(sc_error, sc_conv); printf(" |");
    print_valor(nrm_xi, nrm_conv); print_error(nrm_error, nrm_conv);
    printf("\n");

    while (iter < max_iter && !(pf_conv && nr_conv && sc_conv && nrm_conv)) {
        iter++;

        if (!pf_conv) {
            pf_x_ip1 = g(pf_xi);
            pf_error =fabs((pf_x_ip1 - pf_xi) / pf_x_ip1);
            pf_xi = pf_x_ip1;
            pf_conv = (pf_error <= E_max);
        }

        if (!nr_conv) {
            nr_x_ip1 = nr_xi - f(nr_xi) / df(nr_xi);
            nr_error =fabs((nr_x_ip1 - nr_xi) / nr_x_ip1);
            nr_xi = nr_x_ip1;
            nr_conv = (nr_error <= E_max);
        }

        if (!sc_conv) {
            if (fabs(f(sc_x0) - f(sc_x1)) < 1e-15) {
                sc_conv = 1;
            } else {
                sc_x_ip1 = sc_x1 - f(sc_x1) * (sc_x0 - sc_x1) / (f(sc_x0) - f(sc_x1));
                sc_error =fabs((sc_x_ip1 - sc_x1) / sc_x_ip1);
                sc_x0 = sc_x1;
                sc_x1 = sc_x_ip1;
                sc_conv = (sc_error <= E_max);
            }
        }

        if (!nrm_conv) {
            U = f(nrm_xi) / df(nrm_xi);
            dU = (pow(df(nrm_xi), 2) - f(nrm_xi) * ddf(nrm_xi)) / pow(df(nrm_xi), 2);
            if (fabs(dU) < 1e-15) {
                nrm_conv = 1;
            } else {
                nrm_x_ip1 = nrm_xi - U / dU;
                nrm_error =fabs((nrm_x_ip1 - nrm_xi) / nrm_x_ip1);
                nrm_xi = nrm_x_ip1;
                nrm_conv = (nrm_error <= E_max);
            }
        }

        printf("%3d  |", iter);
        print_valor(pf_xi, pf_conv); print_error(pf_error, pf_conv); printf(" |");
        print_valor(nr_xi, nr_conv); print_error(nr_error, nr_conv); printf(" |");
        print_valor(sc_x1, sc_conv); print_error(sc_error, sc_conv); printf(" |");
        print_valor(nrm_xi, nrm_conv); print_error(nrm_error, nrm_conv);
        printf("\n");
    }

    printf("-----------------------------------------------------------------------------------------------------------------\n");
    printf("Raiz real = %.6f\n", 0.567143);
    return 0;
}