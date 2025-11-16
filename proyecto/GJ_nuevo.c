#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

int main(int argc, char *argv[]) {
    FILE *archivo = fopen("matriz.txt", "r");
    if (!archivo) {
        printf("Error: No se encontro el archivo 'matriz.txt'.\n");
        return 1;
    }

    int n;
    if (fscanf(archivo, "%d", &n) != 1) {
        printf("Error: No se pudo leer el tamano 'n' de la matriz desde 'matriz.txt'.\n");
        fclose(archivo);
        return 1;
    }
    fclose(archivo);

    int total_args = n * n + n;
    if (argc != total_args + 1) {
        printf("Error: Se esperaban %d valores en la linea de comandos (%d para A y %d para b), pero se recibieron %d.\n",
               total_args, n * n, n, argc - 1);
        return 1;
    }

    // Asignar matriz aumentada 
    double **Ab = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        Ab[i] = (double *)malloc((n + 1) * sizeof(double));
    }

    int ind = 1;

    // Leer A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Ab[i][j] = atof(argv[ind++]);
        }
    }

    // Leer b
    for (int i = 0; i < n; i++) {
        Ab[i][n] = atof(argv[ind++]);
    }

    // Imprimir A y b
    printf("Sistema A x = b (A es %dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%10.4f ", Ab[i][j]);
        }
        printf(" | %10.4f\n", Ab[i][n]);
    }

    double det = 1.0;
    int intercambios = 0;
    double max_pivot = 0.0;
    double min_pivot = DBL_MAX;

    // Eliminación gaussiana con pivoteo parcial
    for (int k = 0; k < n; k++) {
        // Pivoteo parcial
        int fila_pivote = k;
        double max_val = fabs(Ab[k][k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(Ab[i][k]) > max_val) {
                max_val = fabs(Ab[i][k]);
                fila_pivote = i;
            }
        }

        if (fila_pivote != k) {
            for (int j = 0; j <= n; j++) {
                double temp = Ab[k][j];
                Ab[k][j] = Ab[fila_pivote][j];
                Ab[fila_pivote][j] = temp;
            }
            intercambios++;
        }

        if (fabs(Ab[k][k]) < 1e-12) {
            det = 0.0;
        } else {
            double pivote_abs = fabs(Ab[k][k]);
            if (pivote_abs > max_pivot) max_pivot = pivote_abs;
            if (pivote_abs < min_pivot) min_pivot = pivote_abs;

            det *= Ab[k][k]; // antes de normalizar

            // Normalizar fila k
            double pivote = Ab[k][k];
            for (int j = k; j <= n; j++) {
                Ab[k][j] /= pivote;
            }

            // Eliminacion hacia abajo
            for (int i = k + 1; i < n; i++) {
                double factor = Ab[i][k];
                for (int j = k; j <= n; j++) {
                    Ab[i][j] -= factor * Ab[k][j];
                }
            }
        }

        // Mostrar paso
        printf("Matriz despues del paso %d:\n", k + 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (fabs(Ab[i][j]) < 1e-10) Ab[i][j] = 0.0;
                printf("%10.4f ", Ab[i][j]);
            }
            if (fabs(Ab[i][n]) < 1e-10) Ab[i][n] = 0.0;
            printf(" | %10.4f\n", Ab[i][n]);
        }
    }

    if (intercambios % 2 == 1) {
        det = -det;
    }

    // Resolver si está bien condicionada
    if (fabs(det) >= 1e-12) {
        double *x = (double *)malloc(n * sizeof(double));
        for (int i = n - 1; i >= 0; i--) {
            x[i] = Ab[i][n];
            for (int j = i + 1; j < n; j++) {
                x[i] -= Ab[i][j] * x[j];
            }
        }

        printf("Solucion:\n");
        for (int i = 0; i < n; i++) {
            printf("x[%d] = %12.6f\n", i + 1, x[i]);
        }
        free(x); //liberar memoria de x
    } else {
        printf("El determinante es 0. No tiene solucion unica.\n");
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(Ab[i]);
    }
    free(Ab);

    return 0;
}