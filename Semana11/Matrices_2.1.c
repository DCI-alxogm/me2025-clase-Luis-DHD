#include <stdio.h>
#include <math.h> 

#define FILAS_A 2
#define COLS_A 3
int main() {
    // Matriz A (3x3)
    double A[FILAS_A][COLS_A] = {
        {1, 2, 10},
        {1.05, 2, 10.4},
    };
    printf("Matriz A (%dx%d):\n", FILAS_A, COLS_A);
    for (int i = 0; i < FILAS_A; i++) {
        for (int j = 0; j < COLS_A; j++) {
            printf("%8.2f ", A[i][j]);
        }
        printf("\n");
    }
float pivot[3];
for (int i=0;i<FILAS_A;i++){
    for (int j=0;j<COLS_A;j++){
if (i==j){
    if (A[i][j]!=0){
    continue;
    }
    for (int k=0; k<FILAS_A; k++){
        pivot[k]=A[i][k];
        A[i][k]=A[i+1][k];
        A[i+1][k]=pivot[k];
    }
    }
}
}
    printf("Matriz A (%dx%d):\n", FILAS_A, COLS_A);
    for (int i = 0; i < FILAS_A; i++) {
        for (int j = 0; j < COLS_A; j++) {
            printf("%8.2f ", A[i][j]);
        }
        printf("\n");
    }
    for (int k = 0; k < FILAS_A ; k++) { 
        printf("Eliminando columna %d \n", k + 1, k + 1);
        for (int i = k + 1; i < FILAS_A; i++) {
            double factor = A[i][k] / A[k][k];
            for (int j = 0; j < COLS_A; j++) {
                A[i][j] =A[i][j]- factor * A[k][j];
            }
        }

        printf("Matriz A  (%d):\n", k + 1);
        for (int i = 0; i < FILAS_A; i++) {
            for (int j = 0; j < COLS_A; j++) {
                printf("%10.4f ", A[i][j]);
            }
            printf("\n");
        }
    }


    return 0;
}