#include <stdio.h>
#include <math.h>
float fa(float a) {
    return a*a+a;
}
float fb(float b) {
    return b*b+b;
}
float fk(float k) {
    return k*k+k;
}
int main() {
    float a,b,k,E_max,k_old, fk, fa, fb;
    printf("Ingrese el límite inferior:"); scanf("%f",&a);
    printf("Ingrese el límite superior: "); scanf("%f",&b);
    printf("Ingrese el error máximo: "); scanf("%f",&E_max);
    if (fa*fb<0){
        k=(a+b)/2;
        k_old=k;
        if(fk*fa<0){
            b=k;
        }a=k;
    } 




}
