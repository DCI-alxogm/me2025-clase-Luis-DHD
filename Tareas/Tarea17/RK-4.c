//Método de Runge-Kutta 4 orden
#include <stdio.h>
#include <math.h>
//funcion
double f(double x, double y){
    double g=9.81;
    double c=12.5;
    double m=68.1;
    double a=8.3;
    double b=2.2;
    double v_max=46;
    return g-c/m*(y+a*pow((y/v_max),b));
}

int main() {
    double xi, yi,h, x_max;
    double tolerancia, error;
    int iter = 0;
    int max_iter = 1000;
    printf("Ingrese el punto inicial (x): "); scanf("%lf", &xi);
    printf("Ingrese el punto inicial (y): "); scanf("%lf", &yi);
    printf("Ingrese el punto máximo (x_max): "); scanf("%lf", &x_max);
    printf("Ingrese el espaciado (h): "); scanf("%lf", &h);

    printf("Iteracion\t x_i+1\t\t y_i+1\t\t f(x,y)\t\t Error\n");
    printf("-------------------------------------------------------------------------------------------\n");

    error = 1;
    
    while (xi<x_max) {
        //a1=1/6, a2=1/3, a3=1/3, a4=1/6
        //p1=p2=1/2, q11=1/2=q22, q33=1, p3=1
        double k1= f(xi,yi);
        double k2= f(xi+0.5*h,yi+0.5*h*k1);
        double k3= f(xi+0.5*h,yi+0.5*h*k2);
        double k4= f(xi+1*h,yi+1*h*k3);
        double yip1 = yi + (h/6)*(k1+2*k2+2*k3+k4);
        double xip1 = xi+h;
        error = (yip1-yi)/yip1;
        xi = xip1;
        yi = yip1;
        iter++;
        printf("%d\t\t%.8lf\t%.8lf\t%.8lf\t%.2e\n", iter, xip1, yip1, f(xip1, yip1), error);
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Resultado final: x = %.8lf, y = %.8lf, f = %.8lf\n", xi, yi, f(xi, yi));
    return 0;
}