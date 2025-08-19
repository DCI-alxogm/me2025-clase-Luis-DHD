#include <stdio.h>

int main() {
    int num;
    printf("Ingrese un número: ");
    scanf("%d", &num);  // Falta el formato %d y el operador &

    if (num % 2 == 0) {
        printf("El número ingresado es par\n");
    } else {
        printf("El número ingresado es impar\n");
    }

    return 0;
}