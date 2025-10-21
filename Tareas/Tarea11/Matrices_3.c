#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    // Leer dimensiones desde archivo
    FILE *archivo = fopen("matriz.txt", "r");
    if (!archivo) {
        printf("Error: No se encontro el archivo 'matriz.txt'.\n");
        return 1;
    }

    int filas, cols;
    if (fscanf(archivo, "%d %d", &filas, &cols) != 2) {
        printf("Error: No se pudieron leer las dimensiones de la matriz.\n");
        fclose(archivo);
        return 1;
    }
    fclose(archivo);

    int elementos_tot = filas * cols;

    // Verificar los elementos
    if (argc != elementos_tot + 1) {
        printf("Error: Se esperaban %d valores en la linea de comandos, pero se recibieron %d.\n",
               elementos_tot, argc - 1);
        return 1;
    }

    // Memoria dinámica de la matriz
    double **A = (double **)malloc(filas * sizeof(double *));
    for (int i = 0; i < filas; i++) {
        A[i] = (double *)malloc(cols * sizeof(double));
    }

    // Leer los elementos 
    int idx = 1; // argv[0] es el nombre del programa
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            A[i][j] = atof(argv[idx++]);
        }
    }

    //Matriz original
    printf("Matriz A (%dx%d):\n", filas, cols);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%8.2f ", A[i][j]);
        }
        printf("\n");
    }

    // Pivot 
    for (int i = 0; i < filas && i < cols - 1; i++) {
        if (A[i][i] == 0) {
            int fila_pivot = -1;
            for (int k = i + 1; k < filas; k++) {
                if (A[k][i] != 0) {
                    fila_pivot= k;
                    break;
                }
            }
            if (fila_pivot != -1) {
                for (int j = 0; j < cols; j++) {
                    double temp = A[i][j];
                    A[i][j] = A[fila_pivot][j];
                    A[fila_pivot][j] = temp;
                }
            }
        }
    }

    printf("Matriz despues del pivot:\n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%8.2f ", A[i][j]);
        }
        printf("\n");
    }

   
    double max_pivot = 100;
    double min_pivot = 0.01;


    // Eliminación con normalización
    for (int k = 0; k < filas && k < cols - 1; k++) {
        if (fabs(A[k][k]) < 1e-12) {
            printf("pivot cercano a cero en fila %d. Saltando columna %d.\n", k, k + 1);
            continue;
        }

        double abs_pivot = fabs(A[k][k]);
        if (abs_pivot > max_pivot) max_pivot = abs_pivot;
        if (abs_pivot < min_pivot) min_pivot = abs_pivot;

        //Evaluación del condicionamiento
    double cond_est = (min_pivot > 0) ? max_pivot / min_pivot : -1;
    printf("Evaluacion del condicionamiento \n");
    if (cond_est > 0) {
        printf("Numero de condicion estimado: %.4e\n", cond_est);
        if (cond_est > 1e12) printf("Sistema mal condicionado.\n");
        else if (cond_est > 1e8) printf(" Sistema moderadamente mal condicionado.\n");
        else if (cond_est > 1e4) printf(" Sistema ligeramente mal condicionado.\n");
        else printf("Sistema bien condicionado.\n");
    } else {
        printf(" No se pudo estimar el condicionamiento (pivot nulo).\n");
    }

        // Normalizar
        double pivote = A[k][k];
        for (int j = k; j < cols; j++) {
            A[k][j] /= pivote;
        }

        // Eliminar hacia abajo
        for (int i = k + 1; i < filas; i++) {
            double factor = A[i][k];
            for (int j = k; j < cols; j++) {
                A[i][j] -= factor * A[k][j];
            }
        }
        printf("\nMatriz despues del paso %d:\n", k + 1);
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < cols; j++) {
                if (fabs(A[i][j]) < 1e-10) A[i][j] = 0.0;
                printf("%10.4f ", A[i][j]);
            }
            printf("\n");
        }
    }

    // Matriz final 
    printf("\n Matriz reducida \n");
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            if (fabs(A[i][j]) < 1e-10) A[i][j] = 0.0;
            printf("%10.4f ", A[i][j]);
        }
        printf("\n");
    }

    //  Resolver el sistema 
    if (filas == cols - 1) {
        int compatible = 1;
        double *x = (double *)malloc(filas * sizeof(double));

        // Verificar filas inconsistentes
        for (int i = 0; i < filas; i++) {
            int ceros = 1;
            for (int j = 0; j < cols - 1; j++) {
                if (fabs(A[i][j]) > 1e-10) {
                    ceros = 0;
                    break;
                }
            }
            if (ceros && fabs(A[i][cols - 1]) > 1e-10) {
                compatible = 0;
                break;
            }
        }

        if (compatible) {
            // Solución
            for (int i = 0; i < filas; i++) {
                x[i] = A[i][cols - 1];
            }

            printf("\n Solucion del sistema\n");
            for (int i = 0; i < filas; i++) {
                printf("x[%d] = %10.6f\n", i + 1, x[i]);
            }
            free(x);
        } else {
            printf("\n Sistema incompatible (fila inconsistente detectada).\n");
        }
    } else {
        printf("Sistema no cuadrado. No se resuelve automaticamente.\n");
    }

    // Liberar memoria
    for (int i = 0; i < filas; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}