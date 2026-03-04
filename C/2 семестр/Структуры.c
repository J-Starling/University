#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>

struct address {
    char *country;
    char *city;
    char *street;
    int house;
    int apartment;
};

typedef struct address Address;

void manual(Address *, int);
void ran(Address *, int);
void print(Address *, int);

void main() {
    srand(time(NULL));
    int q, n, i;
    Address *list;
    printf("Введите количество адресов:\n");
    scanf("%d", &n);
    list=(Address *)malloc(n*sizeof(Address));
    printf("Введите 0, если хотите ввести адреса вручную, иначе - любое другое число:\n");
    scanf("%d", &q);
    if (q==0){
        manual(list,n);
    }
    else{
        ran(list,n);
    }
    print(list,n);
    for (i=0;i<n;i++){
        free(list[i].country);
        free(list[i].city);
        free(list[i].street);
    }
    free(list);
}

void print(Address *list, int n){
    int i;
    printf("\nАдреса:\n");
    for (i=0;i<n;i++){
        printf("\nCтрана %s, город %s, улица %s, дом %d, квартира %d",
        list[i].country, list[i].city, 
        list[i].street, list[i].house,
        list[i].apartment);
    }
}

void manual(Address *list, int n){
    int i;
    for (i=0;i<n;i++){
        printf("\nВведите страну (%d):\n",i+1);
        list[i].country=(char *)malloc(20*sizeof(char));
        scanf("%s", list[i].country);
        printf("\nВведите город (%d):\n",i+1);
        list[i].city=(char *)malloc(20*sizeof(char));
        scanf("%s", list[i].city);
        printf("\nВведите улицу (%d):\n",i+1);
        list[i].street=(char *)malloc(20*sizeof(char));
        scanf("%s", list[i].street);
        printf("\nВведите дом (%d):\n",i+1);
        scanf("%d", &list[i].house);
        printf("\nВведите квартиру (%d):\n",i+1);
        scanf("%d", &list[i].apartment);
    }
}

void ran(Address *list, int n){
    int i;
    char *s=(char *)malloc(30*sizeof(char));
    char *countries[]={"Россия", "Беларусь", "Сербия", "Германия", "Великобритания", "Италия", "Франция", "Америка"};
    char *cities[]={"Москва", "Санкт-Петербург", "Минск", "Бобруйск", "Белград", "Нови-Сад", "Берлин", "Мюнхен", "Лондон", "Манчестер", "Рим", "Флоренция", "Париж", "Марсель", "Вашингтон", "Майами"};
    char *streets[]={"Лесная", "Центральная", "Университетская", "Парковая", "Главная", "Школьная"};
    for (i=0;i<n;i++){
        list[i].country=(char *)malloc(100*sizeof(char));
        list[i].city=(char *)malloc(100*sizeof(char));
        list[i].street=(char *)malloc(100*sizeof(char));
        list[i].house=rand() % 50 + 1;
        list[i].apartment=rand() % 500 + 1;
        int k = rand() % 8;
        strcpy(s, countries[k]);
        strcat(list[i].country, s);
        strcpy(s, cities[k*2 + (rand() % 2)]);
        strcat(list[i].city, s);
        strcpy(s, streets[rand() % 6]);
        strcat(list[i].street, s);
    }
    free(s);
}