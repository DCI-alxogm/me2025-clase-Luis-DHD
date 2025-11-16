#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    const int MAX_ITER = 100000;
    const double TOLERANCIA = 1e-6;

    // Leer dimension desde archivo
    FILE *archivo = fopen("matriz.txt", "r");
    if (!archivo) {
        printf("Error: No se encontro el archivo.\n");
        return 1;
    }

    int n;
    if (fscanf(archivo, "%d", &n) != 1) {
        printf("Error: No se pudo leer el tamano 'n' de la matriz desde 'matriz.txt'.\n");
        fclose(archivo);
        return 1;
    }
    fclose(archivo);

    int elementos_totales = n * n + n; 
    if (argc != elementos_totales + 1) {
        printf("Error: Introduce %d elementos en la linea de comandos (%d para A y %d para b).\n",
               elementos_totales, n*n, n);
        return 1;
    }

    // Reservar memoria
    double **A = (double **)malloc(n * sizeof(double *));
    double *b = (double *)malloc(n * sizeof(double));
    double *x = (double *)malloc(n * sizeof(double));      // iteracion actual
    double *x_prev = (double *)malloc(n * sizeof(double)); // iteracion anterior

    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }

    // Leer matriz A
    int ind = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = atof(argv[ind++]);
        }
    }

    // Leer vector b
    for (int i = 0; i < n; i++) {
        b[i] = atof(argv[ind++]);
    }

    // Clcular determinante
    // Hacer una copia de A para no modificar la original
    double **A_copia = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A_copia[i] = (double *)malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            A_copia[i][j] = A[i][j];
        }
    }

    double det = 1.0;
    int singular = 0;
    // Eliminación gaussiana sin pivoteo para el det
    for (int k = 0; k < n; k++) {
        if (fabs(A_copia[k][k]) < 1e-12) {
            // Buscar fila para intercambiar (pivoteo parcial básico)
            int fila_int = -1;
            for (int i = k + 1; i < n; i++) {
                if (fabs(A_copia[i][k]) > 1e-12) {
                    fila_int = i;
                    break;
                }
            }
            if (fila_int == -1) {
                det = 0.0;
                singular = 1;
                break;
            } else {
                // Intercambiar filas
                for (int j = 0; j < n; j++) {
                    double var_temp = A_copia[k][j];
                    A_copia[k][j] = A_copia[fila_int][j];
                    A_copia[fila_int][j] = var_temp;
                }
                det = -det; // cambio de signo por intercambio
            }
        }
        if (!singular) {
            det *= A_copia[k][k];
            // Eliminar
            for (int i = k + 1; i < n; i++) {
                double factor = A_copia[i][k] / A_copia[k][k];
                for (int j = k; j < n; j++) {
                    A_copia[i][j] -= factor * A_copia[k][j];
                }
            }
        }
    }

    printf("Determinante de A: %.6e\n", det);
    // Liberar copia
    for (int i = 0; i < n; i++) {
        free(A_copia[i]);
    }
    free(A_copia);

    // Mostrar matrices y vector
    printf("Matriz A (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%10.4f ", A[i][j]);
        }
        printf("\n");
    }
    printf("Vector b:\n");
    for (int i = 0; i < n; i++) {
        printf("%10.4f\n", b[i]);
    }

    // Verificar que no haya ceros en la diagonal 
    for (int i = 0; i < n; i++) {
        if (fabs(A[i][i]) < 1e-12) {
            printf("\nAdvertencia: A[%d][%d] = 0.\n", i, i);
        }
    }

    // Iniciar las iteraciones x = 0
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    int iter;
    double error;

    // Iteraciones
    for (iter = 0; iter < MAX_ITER; iter++) {
        // Guardar x anterior
        for (int i = 0; i < n; i++) {
            x_prev[i] = x[i];
        }

        // x actual
        for (int i = 0; i < n; i++) {
            double sum = b[i];
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum -= A[i][j] * x[j]; // usa x[j]  si j < i
                }
            }
            if (fabs(A[i][i]) < 1e-12) {
                printf("Error: pivote nulo en fila %d durante iteracion %d.\n", i, iter);
                return 1;
            }
            x[i] = sum / A[i][i];
        }

        // Calcular error 
        error = 0.0;
        for (int i = 0; i < n; i++) {
            double diferencia = fabs(x[i] - x_prev[i]);
            if (diferencia > error) error = diferencia;
        }

        // Verificar 
        if (error < TOLERANCIA) {
            break;
        }
    }

    // Mostrar resultados
    if (iter < MAX_ITER) {
        printf("\nConvergencia alcanzada en %d iteraciones (error = %.2e).\n", iter + 1, error);
    } else {
        printf("\nAdvertencia: No se alcanzo convergencia en %d iteraciones (error final = %.2e).\n", MAX_ITER, error);
    }

    printf("\nSolucion aproximada x:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %12.8f\n", i + 1, x[i]);
    }

    // Verificación: calcular A*x y comparar con b
    printf("\nVerificacion A*x:\n");
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        printf("Fila %d: %12.8f (esperado: %12.8f, error: %.2e)\n", i + 1, sum, b[i], fabs(sum - b[i]));
    }

    // Liberar memoria
    free(x);
    free(x_prev);
    free(b);
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}