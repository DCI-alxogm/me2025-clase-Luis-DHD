#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N_PUNTOS 500
#define N_PARAMS 4

double aw_datos[N_PUNTOS];
double Xe_datos[N_PUNTOS];
int n_datos = 0;

// Modelo 1: Xe = b0 * aw^b1 + b2 * aw^b3
double modelo1(double aw, double b[N_PARAMS]) {
    double b0 = b[0], b1 = b[1], b2 = b[2], b3 = b[3];
    return b0 * pow(aw, b1) + b2 * pow(aw, b3);
}

// Modelo 2: Xe = b0 + b1*x + b2*x^2 + b3*x^3
double modelo2(double aw, double b[N_PARAMS]) {
    if (aw <= 1e-6) aw = 1e-6;
    if (aw >= 1.0) aw = 1.0 - 1e-6;
    double x = log(-log(aw));
    return b[0] + b[1]*x + b[2]*x*x + b[3]*x*x*x;
}

// Chi^2 (suma de cuadrados de residuos)
double chi2_modelo1(double b[N_PARAMS]) {
    double sum = 0.0;
    for (int i = 0; i < n_datos; i++) {
        double pred = modelo1(aw_datos[i], b);
        double res = Xe_datos[i] - pred;
        sum += res * res;
    }
    return sum;
}

double chi2_modelo2(double b[N_PARAMS]) {
    double sum = 0.0;
    for (int i = 0; i < n_datos; i++) {
        double pred = modelo2(aw_datos[i], b);
        double res = Xe_datos[i] - pred;
        sum += res * res;
    }
    return sum;
}

// Gradiente numérico (diferencias centrales)
void gradiente(double (*chi2)(double*), double b[N_PARAMS], double grad[N_PARAMS]) {
    const double h = 1e-3;
    double b_mas[N_PARAMS], b_menos[N_PARAMS];
    
    for (int j = 0; j < N_PARAMS; j++) {
        for (int k = 0; k < N_PARAMS; k++) {
            b_mas[k] = b[k];
            b_menos[k] = b[k];
        }
        b_mas[j] += h;
        b_menos[j] -= h;
        
        double f_mas = chi2(b_mas);
        double f_menos = chi2(b_menos);
        grad[j] = (f_mas - f_menos) / (2 * h);
    }
}

// Gradiente descendente
void gradiente_descendente(double (*chi2)(double*), double b[N_PARAMS], double *chi2_final) {
    double ta = 0.0001;     // tasa de aprendizaje
    const int max_iter = 5000;
    const double tol = 1e-8;
    
    double grad[N_PARAMS];
    double chi2_prev = chi2(b);
    
    for (int iter = 0; iter < max_iter; iter++) {
        gradiente(chi2, b, grad);
        
        // Actualizar parámetros
        for (int j = 0; j < N_PARAMS; j++) {
            b[j] -= ta * grad[j];
        }
        
        double chi2_actual = chi2(b);
        
        if (fabs(chi2_actual - chi2_prev) < tol) {
            break;
        }
        chi2_prev = chi2_actual;
        
        // Ajuste adaptativo de la tasa de aprendizaje
        if (iter % 500 == 0 && iter > 0) {
            ta *= 0.9;
        }
    }
    
    *chi2_final = chi2(b);
}

// Cargar datos 
int cargar_datos(const char* archivo) {
    FILE *fp = fopen(archivo, "r");
    if (!fp) {
        printf("Error: no se pudo abrir %s\n", archivo);
        return -1;
    }
    char line[256];
    
    n_datos = 0;
    double saltar;
    while (fscanf(fp, "%lf %lf %lf %lf", &saltar, &aw_datos[n_datos], &saltar, &Xe_datos[n_datos]) == 4) {
        n_datos++;
        if (n_datos >= N_PUNTOS) break;
    }
    fclose(fp);
    return 0;
}

// MAIN
int main() {
    const char* archivos[] = {
        "roasted_25.dat", "roasted_35.dat", "roasted_45.dat",
        "medium_25.dat", "medium_35.dat", "medium_45.dat",
        "fine_25.dat",   "fine_35.dat",   "fine_45.dat"
    };
    const char* nombres[] = {
        "Roasted beans (25°C)", "Roasted beans (35°C)", "Roasted beans (45°C)",
        "Medium grind (25°C)",  "Medium grind (35°C)",  "Medium grind (45°C)",
        "Fine grind (25°C)",    "Fine grind (35°C)",    "Fine grind (45°C)"
    };
    int n_archivos = sizeof(archivos) / sizeof(archivos[0]);

    printf("AJUSTE POR MÍNIMOS CUADRADOS\n");
    printf("====================================================\n");

    for (int idx = 0; idx < n_archivos; idx++) {
        if (cargar_datos(archivos[idx]) != 0) {
            continue;
        }

        // Inicialización para Modelo 1
        double b1[N_PARAMS] = {1.0, 1.0, 1.0, 1.0};
        // Inicialización para Modelo 2
        double b2[N_PARAMS] = {1.0, 0.1, 0.01, 0.001};
        double chi2_1 = 0.0, chi2_2 = 0.0;

        gradiente_descendente(chi2_modelo1, b1, &chi2_1);
        gradiente_descendente(chi2_modelo2, b2, &chi2_2);

        printf("\n%s\n", nombres[idx]);
        printf("M1: b0=%.4f, b1=%.4f, b2=%.4f, b3=%.4f | Chi2=%.6f\n",
               b1[0], b1[1], b1[2], b1[3], chi2_1);
        printf("M2: b0=%.4f, b1=%.4f, b2=%.4f, b3=%.4f | Chi2=%.6f\n",
               b2[0], b2[1], b2[2], b2[3], chi2_2);
        printf("-> Mejor: %s\n", (chi2_1 < chi2_2) ? "Modelo 1" : "Modelo 2");
        printf("----------------------------------------");
    }

    return 0;
}