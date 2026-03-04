/*Дана матрица. Если она симметрична относительно побочной оси, сформировать новую матрицу перестановкой столбцов исходной так, чтобы элементы последней строки были расположены по убыванию, иначе - по возрастанию.*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void r(int,float **);
void ran(int,float **);
void pr(int,float **);
float ** fun(int, float **);
int main() {
    srand(time(NULL));
    int q=1,f=0,i,j;
    float n,**ppA,**ppB;
    do{
        printf("\nПожалуйста, введите порядок квадратной матрицы: ");
        scanf("%f",&n);
        while (n<1 || n!=(int)n){
            printf("Ошибка! Пожалуйста, введите натуральное n:\n");
            scanf("%f",&n);
        }
        ppA=(float **)calloc(n,sizeof(float *));
        for (i=0;i<n;i++){
            *(ppA+i)=(float *)calloc(n,sizeof(float));
        }
        printf("\nПожалуйста, введите 0, если хотите ввести элементы массива вручную, иначе - любое другое число: ");
        scanf("%d",&f);
        if (f==0){r(n,ppA);}
        else{ran(n,ppA);}
        printf("\nВведённая матрица:\n\n");
        pr(n,ppA);
        ppB=fun(n,ppA);
        printf("\nПолученная матрица:\n\n");
        pr(n,ppB);
        printf("\nПожалуйста, введите 0, если хотите выйти из программы, иначе - любое другое число: ");
        scanf("%d",&q);
        for (i=0;i<n;i++){free(*(ppA+i));}
        free(ppA);
        for (i=0;i<n;i++){free(*(ppB+i));}
        free(ppB);
    }while(q==1);
    printf("Конец.");
    return 0;
}
void r(int n, float ** ppA){
    int i,j;
    printf("\nПожалуйста, введите элементы матрицы:\n\n");
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            scanf("%f", (*(ppA+i)+j));
        }
    }
}
void ran(int n, float ** ppA){
    int i,j;
    float a,b,c=0;
    printf("\nПожалуйста, введите границы случайных чисел a,b:\n\n");
    printf("a=");
    scanf("%f",&a);
    printf("b=");
    scanf("%f",&b);
    if (b<a) {c=a;a=b;b=c;}
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            *(*(ppA+i)+j)=(float)rand()/RAND_MAX*(b-a)+a;
        }
    }
}
void pr(int n,float ** ppA){
    int i,j;
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            printf("%5.4f ",*(*(ppA+i)+j));
        }
        printf("\n");
    }
}
float ** fun(int n, float ** ppA){
    int i,j,k,p=0;
    float t=0, **ppB;
    ppB=(float **)calloc(n,sizeof(float *));
        for (i=0;i<n;i++){
            *(ppB+i)=(float *)calloc(n,sizeof(float));
        }
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            *(*(ppB+i)+j)=*(*(ppA+i)+j);
        }
    }
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            if ((i<n-j-1)&&(*(*(ppA+i)+j)!=*(*(ppA+n-i-1)+n-j-1))){p=1;}
        }
    }
    if (p==0){
        for (i=0;i<n-1;i++){
            for (j=0;j<n-i-1; j++){
                if (*(*(ppB+n-1)+j) < *(*(ppB+n-1)+j+1)) {
                    for (k=0;k<n;k++){
                    t = *(*(ppB+k)+j);
                    *(*(ppB+k)+j) = *(*(ppB+k)+j+1);
                    *(*(ppB+k)+j+1) = t;
                    }
                }
            }
        }
    }
    else{
        for (i=0;i<n-1;i++){
            for (j=0;j<n-i-1; j++){
                if (*(*(ppB+n-1)+j) > *(*(ppB+n-1)+j+1)) {
                    for (k=0;k<n;k++){
                    t = *(*(ppB+k)+j);
                    *(*(ppB+k)+j) = *(*(ppB+k)+j+1);
                    *(*(ppB+k)+j+1) = t;
                    }
                }
            }
        }
    }
    return(ppB);
}