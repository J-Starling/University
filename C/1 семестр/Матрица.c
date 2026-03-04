/*Дана матрица. Если она симметрична относительно побочной оси, сформировать матрицу новую матрицу перестановкой столбцов исходной так, чтобы элементы последней строки были расположены по убыванию, иначе - по возрастанию.*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    srand(time(NULL));
    const int n = 3;
    int q=1,f=0,p=0,i,j,k;
    float A[n][n],B[n][n],a,b,c=0,t=0;
    do{
        printf("\nПожалуйста, введите 0, если хотите ввести элементы массива вручную, иначе - любое другое число: ");
        scanf("%d",&f);
        if (f==0){
            printf("\nПожалуйста, введите элементы матрицы с новой строки:\n\n");
            for (i=0;i<n;i++){
                for (j=0;j<n;j++){
                    scanf("%f",&A[i][j]);
                }
            }
            printf("\nВведённая матрица:\n\n");
            for (i=0;i<n;i++){
                for (j=0;j<n;j++){
                    printf("%.2f ",A[i][j]);
                }
                printf("\n");
            }
        }
        else{
            printf("\nПожалуйста, введите границы случайных чисел a,b:\n\n");
            printf("a=");
            scanf("%f",&a);
            printf("b=");
            scanf("%f",&b);
            if (b<a) {c=a;a=b;b=c;}
            printf("\nВведённая матрица:\n\n");
            for (i=0;i<n;i++){
                for (j=0;j<n;j++){
                    A[i][j]=(float)rand()/RAND_MAX*(b-a)+a;
                    printf("%.2f ",A[i][j]);
                }
                printf("\n");
            }
        }
        for (i=0;i<n;i++){
            for (j=0;j<n;j++){
                B[i][j]=A[i][j];
            }
        }
        for (i=0;i<n;i++){
            for (j=0;j<n;j++){
                if ((i<n-j-1)&&(A[i][j]!=A[n-i-1][n-j-1])){p=1;}
            }
        }
        if (p==0){
            for (i=0;i<n-1;i++){
                for (j=0;j<n-i-1; j++){
                    if (B[n-1][j] < B[n-1][j+1]) {
                        for (k=0;k<n;k++){
                        t = B[k][j];
                        B[k][j] = B[k][j+1];
                        B[k][j+1] = t;
                        }
                    }
                }
            }
        }
        else{
            for (i=0;i<n-1;i++){
                for (j=0;j<n-i-1; j++){
                    if (B[n-1][j] > B[n-1][j+1]) {
                        for (k=0;k<n;k++){
                        t = B[k][j];
                        B[k][j] = B[k][j+1];
                        B[k][j+1] = t;
                        }
                    }
                }
            }
        }
        printf("\nПолученная матрица:\n\n");
        for (i=0;i<n;i++){
            for (j=0;j<n;j++){
                printf("%.2f ",B[i][j]);
            }
            printf("\n");
        }
        printf("\nПожалуйста, введите 0, если хотите выйти из программы, иначе - любое другое число: ");
        scanf("%d",&q);
    }while(q==1);
    printf("Конец.");
    return 0;
}
