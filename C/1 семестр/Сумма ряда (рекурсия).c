#include <stdio.h>
#include <math.h>
float ck (long double);
long double sum (long double, long double);
long double fact (long double);
int main() { 
    int q=1;
    do{
    long double x,n;
    printf("\nПожалуйста, введите количество элементов ряда:\n");
    scanf("%Lf",&n);
    if (n<1 || n!=(int)n){
        printf("n - не натуральное число. Пожалуйста, введите натуральное значение:\n");
        scanf("%Lf",&n);
    }
    printf("Пожалуйста, введите значение переменной X:\n");
    scanf("%Lf",&x);
    printf("Квадрат косинуса от X (в приближении):\n%Lf\n",1-sum(n,x));
    printf("Квадрат косинуса от X:\n%f\n",ck(x));
    printf("Разница:\n%f\n",fabs(ck(x)-1+sum(n,x)));
    printf("Продолжить? (0-нет/1-да)\n");
    scanf("%d",&q);
} while (q!=0);
return 0;
}
float ck (long double x){ 
    return(cos(x)*cos(x)); 
}
long double fact (long double i){
    if (i==0) return 1;
    long double s;
    s=i*fact(i-1);
    return(s);
}
long double st (long double a, long double b){
    if (b==0) return 1;
    long double s;
    s=a*st(a,b-1);
    return(s);
}
long double sum (long double n, long double x){
    long double s,a;
    if (n==1) return x*x;
    s=sum(n-1,x)+st(-1,n+1)*st(2,2*n-1)*st(x,2*n)/fact(2*n);
    return(s);
}