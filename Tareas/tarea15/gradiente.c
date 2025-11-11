#include <stdio.h>
#include <math.h>

// Función 
double f(double x, double y) {
    return 2*x*y + 2*x - x*x - 2*y*y;  
}

// Derivadas parciales 
double dfdx(double x, double y, double h) {
    return (f(x + h, y) - f(x - h, y)) / (2 * h);
}

double dfdy(double x, double y, double h) {
    return (f(x, y + h) - f(x, y - h)) / (2 * h);
}

// g(h) = f(x + h*dx, y + h*dy)
double g(double h, double x, double y, double dx, double dy) {
    double x_ip1 = x + h * dx;
    double y_ip1 = y + h * dy;
    return f(x_ip1, y_ip1);
}

double h_opt(double x, double y, double dx, double dy) {
    double h = 0.1;
    double tol = 1e-8;
    int iter_max = 100;
    for (int i = 0; i < iter_max; i++) {
        double dh = 1e-6;
        double dg = (g(h + dh, x, y, dx, dy) - g(h - dh, x, y, dx, dy)) / (2 * dh);
        if (fabs(dg) < tol) break;
        double ddg = (g(h + dh, x, y, dx, dy) - 2 * g(h, x, y, dx, dy) + g(h - dh, x, y, dx, dy)) / (dh * dh);
        if (fabs(ddg) < 1e-10 || ddg > 0) {
            h *= 0.5;
        } else {
            h = h - dg / ddg;
        }
        if (h < 0) h = 0;
        if (h > 10) h = 10;
    }
    return h;
}

int main() {
    double xi, yi;
    double tolerancia, error;
    int iter = 0;
    int max_iter = 1000;
    printf("Ingrese el punto inicial (x): "); scanf("%lf", &xi);
    printf("Ingrese el punto inicial (y): "); scanf("%lf", &yi);
    printf("Ingrese el error maximo: "); scanf("%lf", &tolerancia);

    printf("Iteracion\t x_i+1\t\t y_i+1\t\t f(x,y)\t\t h_optima\t Error\n");
    printf("-------------------------------------------------------------------------------------------\n");

    error = 1;
    const double h_deriv = 1e-5;  
    
    while (error > tolerancia && iter < max_iter) {
        double dx = dfdx(xi, yi, h_deriv);
        double dy = dfdy(xi, yi, h_deriv);

        double h_optima = h_opt(xi, yi, dx, dy);
        double xip1 = xi + h_optima * dx;
        double yip1 = yi + h_optima * dy;

        error = sqrt((xip1 - xi)*(xip1 - xi) + (yip1 - yi)*(yip1 - yi));
        xi = xip1;
        yi = yip1;
        iter++;
        printf("%d\t\t%.8lf\t%.8lf\t%.8lf\t%.8lf\t%.2e\n", iter, xip1, yip1, f(xip1, yip1), h_optima, error);
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("Resultado final: x = %.8lf, y = %.8lf, f = %.8lf\n", xi, yi, f(xi, yi));
    return 0;
}