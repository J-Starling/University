#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    srand(time(NULL));
    int q=1;
    do{
        int i,j,t,f,a,b,sum,k=0,l=0;
        long S;
        const int n = 5;
        int A[n];
        const int m = 32;
        int B[m];
        printf("\nПожалуйста, введите 0, если хотите ввести элементы массива вручную, иначе - любое другое число: ");
        scanf("%d",&f);
        if (f==0){
            for (i=0;i<n;i++){
                printf("A[%d]=",i);
                scanf("%d",&A[i]);
            }
        }
        else{
            printf("\nПожалуйста, введите натуральные границы случайных чисел a,b:\n");
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
            for (i=0;i<n;i++){
                A[i]=a+rand()%(b-a+1);
                printf("A[%d]=%d\n",i,A[i]);
            }
        }
        for(S=0; S<m; S++) {
            for(i=0, sum=0; i<n; i++) 
            if (S&(1<<i)) {sum+=A[i];}
            B[l]=sum;
            l++;
            }
        for (i=0;i<n-1;i++)
        for (j=0;j<n-i-1; j++)
            if (B[j] > B[j+1]) {
                t = B[j];
                B[j] = B[j+1];
                B[j+1] = t;
                }
        for (i=0;i<m;i++) if (k==B[i]) k++;
        printf("\n");
        for (i=1;i<m;i++){printf("B[%d]=%d\n",i,B[i]);}
        printf("\nМинимальное натуральное число, не представимое суммой элементов массива: %d",k);
        printf("\nПожалуйста, введите 0, если хотите выйти из программы, иначе - любое другое число: ");
        scanf("%d",&q);
    }while(q==1);
    printf("Конец.");
    return 0;
}
