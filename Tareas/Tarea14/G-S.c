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
    if (fscanf(archivo, "%d %d", &n, &n) != 2) {
        printf("Error: El archivo debe ser para una matriz cuadrada.\n");
        fclose(archivo);
        return 1;
    }
    fclose(archivo);

    int total_args = n * n + n;
    if (argc != total_args + 1) {
        printf("Error: Se esperaban %d valores (matriz A de %dx%d + vector b de %d), pero se recibieron %d.\n",
               total_args, n, n, n, argc - 1);
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

    // Mostrar matrices y vector
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
            double diff = fabs(x[i] - x_prev[i]);
            if (diff > error) error = diff;
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