/* Найти минимальное  натуральное число, не представимое никакой суммой элементов массива */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
void r(int , int *);
void ran(int , int *);
float fun(int, int, int *, int *);
void p(int);
int main() {
    srand(time(NULL));
    int f,q=1,k=1,N,i=0,j,t=0;
    long S=0;
    int * pA;
    int * pB;
    do{
        printf("\nПожалуйста, введите количество элементов массива: ");
            scanf("%d",&N);
            while (N<1 || N!=(int)N){
                printf("Ошибка! Пожалуйста, введите натуральное N:\n");
                scanf("%d",&N);
            }
        pA=(int *)calloc(N,sizeof(int));
        pB=(int *)calloc(pow(2,N),sizeof(int));
        printf("\nПожалуйста, введите 0, если хотите ввести элементы массива вручную, иначе - любое другое число: ");
        scanf("%d",&f);
        if (f==0){r(N,pA);}
        else{ran(N,pA);}
        printf("\n");
        for (i=1;i<pow(2,N);i++){
            printf("B[%d]=%f\n",i,fun(N,i,pA,pB));
        }
        for (i=0;i<pow(2,N);i++) if (k==*(pB+i)) k++;
        p(k);
        printf("\nПожалуйста, введите 0, если хотите выйти из программы, иначе - любое другое число: ");
        scanf("%d",&q);
        printf("\n");
        free(pA);
        free(pB);
    }while(q!=0);
    printf("Конец.");
    return 0;
}
void r(int N, int * pA){
    int i;
    printf("\n");
    for (i=0;i<N;i++){
        printf("A[%d]=",i);
        scanf("%d",(pA+i));
        }
}
void ran(int N, int * pA){
    int a,b,i;
    printf("\nПожалуйста, введите натуральные границы случайных чисел a,b:\n\n");
    printf("a=");
    scanf("%d",&a);
    while (a<1 || a!=(int)a){
        printf("Ошибка! Пожалуйста, введите натуральное a:\n");
        printf("a=");
        scanf("%d",&a);
    }
    printf("b=");
    scanf("%d",&b);
    while (b<1 || b!=(int)b){
        printf("Ошибка! Пожалуйста, введите натуральное b:\n");
        printf("b=");
        scanf("%d",&b);
    }
    printf("\n");
    if (b<a) {int c=b;b=a;a=c;}
    for (i=0;i<N;i++){
        *(pA+i)=a+rand()%(b-a+1);
        printf("A[%d]=%d\n",i,*(pA+i));
    }
}
float fun(int N, int k, int * pA, int * pB){
    int sum=0,l=0,t=0,i,j;
    long S=0;
    for(S=0; S<pow(2,N); S++){
        for(i=0, sum=0; i<N; i++){ 
            if (S&(1<<i)) {sum+=*(pA+i);}
        }
        *(pB+l)=sum;
        l++;
    }
    for (i=0;i<pow(2,N)-1;i++){
        for (j=0;j<pow(2,N)-i-1; j++){
            if (*(pB+j) > *(pB+j+1)) {
                t = *(pB+j);
                *(pB+j) = *(pB+j+1);
                *(pB+j+1) = t;
            }
        }
    }
    return *(pB+k);
}
void p(int k){
    printf("\nМинимальное натуральное число, не представимое суммой элементов массива: %d\n",k);
}