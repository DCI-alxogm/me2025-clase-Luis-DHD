#include <stdio.h>
#include <math.h>

double potencia(double base, int exp) {
    double resultado = 1.0;
    for (int i = 0; i < exp; i++) {
        resultado *= base;
    }
    return resultado;
}

double factorial(int n) {
    double fact = 1.0;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

double de_x(int n, double punto) {
    return exp(punto);
}

double dsin_x(int n, double punto) {
    int r = n % 4;
    if (r == 0) return sin(punto);
    else if (r == 1) return cos(punto);
    else if (r == 2) return -sin(punto);
    else return -cos(punto);
}

double dcos_x(int n, double punto) {
    int r = n % 4;
    if (r == 0) return cos(punto);
    else if (r == 1) return -sin(punto);
    else if (r == 2) return -cos(punto);
    else return sin(punto);
}

double dln_x(int n, double punto) {
    if (punto <= -1) return NAN;
    if (n == 0) return log(1 + punto);
    double signo = (n % 2 == 1) ? 1.0 : -1.0;
    for (int i = 1; i < n; i++) {
        signo *= -i;
    }
    return signo / potencia(1 + punto, n);
}


double d1_sobre_1mx(int n, double punto) {
    if (punto == 1) return NAN;
    return factorial(n) / potencia(1 - punto, n + 1);
}

double derivada_n1(char opcion, int n, double xi) {
    int m = n + 1; 
    switch (opcion) {
        case '1': return de_x(m, xi);
        case '2': return dsin_x(m, xi);
        case '3': return dcos_x(m, xi);
        case '4': return dln_x(m, xi);
        case '5': return d1_sobre_1mx(m, xi);
        default: return NAN;
    }
}

int main() {
    double x_i, x_j, Xi, error_max;
    int n_max;
    char opcion;
    printf("Funciones a elegir:\n");
    printf("1. e^x\n2. sin(x)\n3. cos(x)\n4. ln(1+x)\n5. 1/(1-x)\n");

    printf("Ingrese x_i+1: ");   scanf("%lf", &x_j);
    printf("Ingrese x_i: ");   scanf("%lf", &x_i);
    printf("Ingrese  Xi (debe estar entre x_i y x_i+1): "); scanf("%lf", &Xi);
    printf("Grado: "); scanf("%d", &n_max);
    printf("Error maximo permitido: "); scanf("%lf", &error_max);
    printf("Seleccione una funcion (1-5): "); scanf(" %c", &opcion);

    if (opcion == '4' && x_j <= -1) {
        printf("Error: ln(1+x) no esta definido para x <= -1.\n");
        return 1;
    }
    if (opcion == '5' && x_j == 1) {
        printf("Error: 1/(1-x) no esta definido para x = 1.\n");
        return 1;
    }
    if (opcion == '4' && Xi <= -1) {
        printf("Advertencia: Xi <= -1, derivadas de ln(1+x) pueden no estar definidas.\n");
    }
    if (opcion == '5' && Xi == 1) {
        printf("Error: Xi no puede ser 1 para 1/(1-x).\n");
        return 1;
    }

    double suma = 0.0;
    double suma_anterior;
    double error_a;
    double valor_verdadero = NAN;

    printf("\n%3s %18s %15s %18s %18s %18s \n", "n", "Aproximacion", "Error (asociado)", "Valor verdadero", "Error (verdadero)", "Residuo");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    for (int n = 0; n < n_max; n++) {
        double derivada;
        switch (opcion) {
            case '1': derivada = de_x(n, x_i); break;
            case '2': derivada = dsin_x(n, x_i); break;
            case '3': derivada = dcos_x(n, x_i); break;
            case '4': derivada = dln_x(n, x_i); break;
            case '5': derivada = d1_sobre_1mx(n, x_i); break;
            default: printf("Opcion invalida.\n"); return 1;
        }

        if (isnan(derivada)) {
            printf("Error: derivada no definida en x_i para n=%d.\n", n);
            return 1;
        }

        double termino = derivada * potencia(x_j - x_i, n) / factorial(n);
        suma_anterior = suma;
        suma += termino;

        
        error_a = (n == 0) ? 0.0 : fabs(suma - suma_anterior);

        if (isnan(valor_verdadero)) {
            switch (opcion) {
                case '1': valor_verdadero = exp(x_j); break;
                case '2': valor_verdadero = sin(x_j); break;
                case '3': valor_verdadero = cos(x_j); break;
                case '4': valor_verdadero = log(1 + x_j); break;
                case '5': valor_verdadero = 1.0 / (1 - x_j); break;
            }
        }

        double error_verdadero = fabs(valor_verdadero - suma);

        double derivada_n1_val = derivada_n1(opcion, n, Xi);
        if (isnan(derivada_n1_val)) {
            printf("Error: derivada (n+1) no definida en Xi=%.4f.\n", Xi);
            return 1;
        }
        double residuo = (derivada_n1_val * potencia(x_j - x_i, n + 1) / factorial(n + 1));

        printf("%3d %18.10f %15.10f %18.10f %18.10f %18.10f\n",
               n, suma, error_a, valor_verdadero, error_verdadero, residuo);

        if (n > 0 && error_a < error_max) {
            break;
        }
    }

    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("Aproximacion final: %.10f\n", suma);
    printf("Valor verdadero: %.10f\n", valor_verdadero);
    printf("Error asociado final: %.10f\n", fabs(valor_verdadero - suma));
    if (fabs(valor_verdadero) > 1e-10) {
        printf("Error relativo final: %.6f%%\n", fabs(valor_verdadero - suma) / fabs(valor_verdadero) * 100);
    }

    return 0;
}