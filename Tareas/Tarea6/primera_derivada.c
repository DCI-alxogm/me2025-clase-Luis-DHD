#include <stdio.h>
#include <math.h>
int main(){
double x_i,fx_i, fx_j, fx_h, df_adelante, df_atras, df_centro, h, error_rel_adelante, error_rel_atras, error_rel_centro;//x_i= xi, x_j=xi+1 y x_h=xi-1
double df_verdadera;
printf("Ingrese el valor verdadero de df(x):"); scanf("%lf", &df_verdadera);
printf("Ingrese x_i: "); scanf("%lf",&x_i);
printf("Ingrese f(x_i): "); scanf("%lf",&fx_i);
printf("Ingrese f(x_i+1): "); scanf("%lf",&fx_j);
printf("Ingrese f(x_i-1): "); scanf("%lf",&fx_h);
printf("Ingrese h: "); scanf("%lf",&h);
df_adelante=(fx_j-fx_i)/h;
df_atras=(fx_i-fx_h)/h;
df_centro=(fx_j-fx_h)/(2*h);
error_rel_adelante= fabs((df_verdadera-df_adelante)/df_verdadera);
error_rel_atras= fabs((df_verdadera-df_atras)/df_verdadera);
error_rel_centro= fabs((df_verdadera-df_centro)/df_verdadera);
printf("\n%3s %18s %18s %18s %18s %18s %18s \n", "x", "df(x) (adelante)", "df(x) (atras)", "df(x) (centro)", "Error (adelante)", "Error (atras)", "Errror (centro)");
printf("----------------------------------------------------------------------------------------------------------------\n");
printf("%3.4f %15.4f %15.4f %15.4f %15.4f %18.4f %18.4f\n",x_i,  df_adelante, df_atras, df_centro, error_rel_adelante, error_rel_atras, error_rel_centro);    
}