#include <stdio.h>

#define FILAS_A 3
#define COLS_A 3
#define FILAS_B 3
#define COLS_B 2

int main() {
    // Matriz A (3x3)
    int A[FILAS_A][COLS_A] = {
        {5, 1, 2},
        {1, 3, 7},
        {2, 7, 8}
    };

    // Matriz B (3x2)
    int B[FILAS_B][COLS_B] = {
        {3, 4},
        {7, 3},
        {8, 1}
    };

    // Matriz resultado C (3x2)
    int C[FILAS_A][COLS_B] = {0}; 

    // Verificar que la multiplicación sea posible
    if (COLS_A != FILAS_B) {
        printf("No se pueden multiplicar las matrices.\n");
        return 1;
    }

    // Multiplicación de matrices
    for (int i = 0; i < FILAS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            for (int k = 0; k < COLS_A; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    printf("C= A * B:\n");
    for (int i = 0; i < FILAS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    printf("A= \n");
    for (int i=0;i<FILAS_A;i++){
        for (int j= 0; j< COLS_A;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }
    printf("a_33= %d \n", A[2][2]);
    printf("a_23= %d \n", A[1][2]);
    printf("a_11= %d \n", A[0][0]);

    int D[FILAS_A][COLS_A]={0};
    int n=0;
    for (int i=n+1; i<FILAS_A; i++){
        double div=A[i][n]/A[n][n];
            for (int j=n; j<COLS_A; j++){
                A[i][j]=A[i][j]- div *A[n][j];
            }
    }
    printf("\nA (n=0)= \n");
    for (int i=0;i<FILAS_A;i++){
        for (int j= 0; j< COLS_A;j++){
            printf("%d ",A[i][j]);
        }
        printf("\n");
    }

    
    return 0;
}