#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    // Leer dimension desde archivo
    FILE *archivo = fopen("matriz.txt", "r");
    if (!archivo) {
        printf("Error: No se encontro el archivo.\n");
        return 1;
    }

    int n;
    if (fscanf(archivo, "%d %d", &n, &n) != 2) {
        printf("Error: El archivo debe ser para una matriz cuadrada.\n");
        fclose(archivo);
        return 1;
    }
    fclose(archivo);

    int elementos_totales = n * n + n; 
    if (argc != elementos_totales + 1) {
        printf("Error: Se esperaban %d valores (matriz A de %dx%d + vector b de %d), pero se recibieron %d.\n",
               elementos_totales, n, n, n, argc - 1);
        return 1;
    }

    // Reservar memoria 
    double **A = (double **)malloc(n * sizeof(double *));
    double **L = (double **)malloc(n * sizeof(double *));
    double **U = (double **)malloc(n * sizeof(double *));
    double *b = (double *)malloc(n * sizeof(double));
    double *x = (double *)malloc(n * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));
    int *piv = (int *)malloc(n * sizeof(int)); 

    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        L[i] = (double *)malloc(n * sizeof(double));
        U[i] = (double *)malloc(n * sizeof(double));
        piv[i] = i; 
    }

    // Leer matriz A
    int idx = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = atof(argv[idx++]);
        }
    }

    // Leer vector b
    for (int i = 0; i < n; i++) {
        b[i] = atof(argv[idx++]);
    }

    // Mostrar matriz y vector
    printf("Matriz A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%10.4f ", A[i][j]);
        }
        printf("\n");
    }
    printf("\nVector b:\n");
    for (int i = 0; i < n; i++) {
        printf("%10.4f\n", b[i]);
    }

    //Factorización LU 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            U[i][j] = A[i][j];
            L[i][j] = 0.0;
        }
        L[i][i] = 1.0; 
    }

    // Factorización
    for (int k = 0; k < n - 1; k++) {
        int fila_max = k;
        double max_val = fabs(U[k][k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(U[i][k]) > max_val) {
                max_val = fabs(U[i][k]);
                fila_max= i;
            }
        }

        if (max_val < 1e-12) {
            printf("Error: Matriz singular o casi singular en columna %d.\n", k);
            return 1;
        }

        // Intercambiar filas en U
        if (fila_max != k) {
            for (int j = 0; j < n; j++) {
                double temp = U[k][j];
                U[k][j] = U[fila_max][j];
                U[fila_max][j] = temp;
            }
            // Intercambiar en el vector de pivot
            int temp_p = piv[k];
            piv[k] = piv[fila_max];
            piv[fila_max] = temp_p;
            // Intercambiar filas en L
            for (int j = 0; j < k; j++) {
                double temp = L[k][j];
                L[k][j] = L[fila_max][j];
                L[fila_max][j] = temp;
            }
        }

        //Eliminación 
        for (int i = k + 1; i < n; i++) {
            L[i][k] = U[i][k] / U[k][k];
            for (int j = k; j < n; j++) {
                U[i][j] -= L[i][k] * U[k][j];
            }
        }
    }

    // Imprimir L y U 
    printf("\nMatriz L:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i) printf("%10.4f ", 0.0);
            else        printf("%10.4f ", L[i][j]);
        }
        printf("\n");
    }

    printf("\nMatriz U:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < i) printf("%10.4f ", 0.0);
            else       printf("%10.4f ", U[i][j]);
        }
        printf("\n");
    }

    //Aplicar pivot a b
    double *Pb = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        Pb[i] = b[piv[i]];
    }

    // Ly = Pb
    for (int i = 0; i < n; i++) {
        y[i] = Pb[i];
        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
    }

    // Ux = y 
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        if (fabs(U[i][i]) < 1e-12) {
            printf("Error: Sistema singular al resolver Ux = y.\n");
            return 1;
        }
        x[i] /= U[i][i];
    }

    // Imprimir solución 
    printf("\nSolucion x:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %10.6f\n", i + 1, x[i]);
    }

    //  Verificación: calcular Ax y comparar con b 
    printf("\nVerificacion A*x:\n");
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        printf("Fila %d: %10.6f (esperado: %10.6f)\n", i + 1, sum, b[i]);
    }

    // Liberar memoria 
    free(Pb);
    free(y);
    free(x);
    free(b);
    free(piv);
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A);
    free(L);
    free(U);

    return 0;
}