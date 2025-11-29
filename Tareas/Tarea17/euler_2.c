//Método de Euler
#include <stdio.h>
#include <math.h>
//funcion
double f_r(double t, double r, double v) {
    return v;  // dr/dt = v
}

double f_v(double t, double r, double v) {
    if (r <= 0) r = 1.0; //evitar números muy grandes o muy pequeños
    double G=6.67e-11;
    double M=5.972e24;
    return -G*M / (r * r); // dv/dt = -mu / r^2
}
int main() {
    double ti, ri, vi, h, t_max;
    int iter=0;

    printf("Ingrese el tiempo inicial (t): "); scanf("%lf", &ti);
    printf("Ingrese la posicion inicial (r) en metros: "); scanf("%lf", &ri);
    printf("Ingrese la velocidad inicial (v) en m/s: "); scanf("%lf", &vi);
    printf("Ingrese el tiempo maximo (t_max): "); scanf("%lf", &t_max);
    printf("Ingrese el espaciado (h): "); scanf("%lf", &h);

    printf("Iteracion\t t_i+1\t\t r_i+1\t\t\t v_i+1\t\t\n");
    printf("-------------------------------------------------------------------------------------------\n");

    while (ti < t_max && ri > 6.371e6) { // detener si toca la Tierra (ri = 6371 km)
        double rip1 = ri + h * f_r(ti, ri, vi); 
        double vip1 = vi + h * f_v(ti, ri, vi);  
        double tip1 = ti + h;

        ti = tip1;
        ri = rip1;
        vi = vip1;
        iter++;

        printf("%d\t\t%.2lf\t\t%.2lf\t\t%.2lf\t\t\n", iter, ti, ri, vi);
    }

    printf("-------------------------------------------------------------------------------------------\n");
    printf("Resultado final: t = %.2lf s, r = %.2lf m (%.0lf km), v = %.2lf m/s\n",
           ti, ri, ri/1000.0, vi);

    return 0;
}