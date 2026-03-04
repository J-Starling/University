#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct address {
    char *country;
    char *city;
    char *street;
    int house;
    int apartment;
};

typedef struct address Address;

struct group {
    int n;
    Address *A;
};

typedef struct group Group;

void manual(Address *, int);
void ran(Address *, int);
void print(Address *, int);
void manual2(Group);
void ran2(Group);
void print2(Group);
void shaker_sort(Group);
void swap(Address *, Address *);
void quick_sort(Address *, int, int);
int partition(Address *, int, int);

void main() {
    srand(time(NULL));
    int f = 0, q, i, s;
    Group groups;
    
    do {
        printf("Введите количество адресов:\n");
        scanf("%d", &groups.n);
        groups.A = (Address *) malloc(groups.n * sizeof(Address));
        printf("Введите 0, если хотите ввести адреса вручную, иначе - любое другое число:\n");
        scanf("%d", &q);
        if (q == 0) {
            manual2(groups);
        } else {
            ran2(groups);
        }
        printf("Какой сортировкой воспользоваться?\n0 - Шейкерная сортировка\n1 - Быстрая сортировка\nИначе - не сортировать:\n");
        scanf("%d", &s);
        if (s == 0) {
            shaker_sort(groups);
        } else if (s == 1) {
            quick_sort(groups.A, 0, groups.n - 1);
        }
        print2(groups);
        for (i = 0; i < groups.n; i++) {
            free(groups.A[i].country);
            free(groups.A[i].city);
            free(groups.A[i].street);
        }
        free(groups.A);
        groups.A = NULL;
        printf("\n\nПерезапустить программу? 0 - да, иначе - нет.\n");
        scanf("%d", &f);
    } while (f == 0);
}

void print(Address *list, int n){
    int i;
    for (i=0;i<n;i++){
        printf("\nCтрана %s, город %s, улица %s, дом %d, квартира %d",
        list[i].country, list[i].city, 
        list[i].street, list[i].house,
        list[i].apartment);
    }
}

void manual(Address *list, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("\nВведите страну (%d):\n", i + 1);
        list[i].country = (char *) malloc(20 * sizeof(char));
        scanf("%s", list[i].country);
        printf("\nВведите город (%d):\n", i + 1);
        list[i].city = (char *) malloc(20 * sizeof(char));
        scanf("%s", list[i].city);
        printf("\nВведите улицу (%d):\n", i + 1);
        list[i].street = (char *) malloc(20 * sizeof(char));
        scanf("%s", list[i].street);
        printf("\nВведите номер дома (%d):\n", i + 1);
        scanf("%d", &list[i].house);
        printf("\nВведите номер квартиры (%d):\n", i + 1);
        scanf("%d", &list[i].apartment);
    }
}

void ran(Address *list, int n) {
    int i;
    char *s;
    const char *countries[] = {"Россия", "Беларусь", "Сербия", "Германия", "Великобритания", "Италия", "Франция", "Америка"};
    const char *cities[] = {"Москва", "Санкт-Петербург", "Минск", "Бобруйск", "Белград", "Нови-Сад", "Берлин", "Мюнхен", "Лондон", "Манчестер", "Рим", "Флоренция", "Париж", "Марсель", "Вашингтон", "Майами"};
    const char *streets[] = {"Лесная", "Центральная", "Университетская", "Парковая", "Главная", "Школьная"};
    
    for (i = 0; i < n; i++) {
        int k = rand() % 8;
        s = (char *) malloc(strlen(countries[k]) + 1);
        strcpy(s, countries[k]);
        list[i].country = (char *) malloc(strlen(s) + 1);
        strcpy(list[i].country, s);
        free(s);
        
        k = k * 2 + (rand() % 2);
        s = (char *) malloc(strlen(cities[k]) + 1);
        strcpy(s, cities[k]);
        list[i].city = (char *) malloc(strlen(s) + 1);
        strcpy(list[i].city, s);
        free(s);
        
        k = rand() % 6;
        s = (char *) malloc(strlen(streets[k]) + 1);
        strcpy(s, streets[k]);
        list[i].street = (char *) malloc(strlen(s) + 1);
        strcpy(list[i].street, s);
        free(s);
        
        list[i].house = rand() % 50 + 1;
        list[i].apartment = rand() % 500 + 1;
        
        // в следующий раз использовать strdup
    }
}

void print2(Group groups) {
    printf("\nГруппа адресов:\n");
    print(groups.A, groups.n);
}

void manual2(Group groups) {
    printf("\nОграничение на ввод - 20 символов в каждой строке!\n");
    manual(groups.A, groups.n);
}

void ran2(Group groups) {
    ran(groups.A, groups.n);
}

void swap(Address *a, Address *b) {
    Address temp = *a;
    *a = *b;
    *b = temp;
}

void shaker_sort(Group groups) {
    int i, j;
    for (i = 1; i <= groups.n / 2; i++) {
        for (j = i - 1; j < groups.n - i; j++) {
            if (groups.A[j].apartment > groups.A[j + 1].apartment) {
                swap(&groups.A[j], &groups.A[j + 1]);
            }
        }
        for (j = groups.n - i - 1; j >= i; j--) {
            if (groups.A[j].apartment < groups.A[j - 1].apartment) {
                swap(&groups.A[j], &groups.A[j - 1]);
            }
        }
    }
}

int partition(Address *a, int low, int high) {
    int pivot = a[high].apartment;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j].apartment <= pivot) {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return i + 1;
}

void quick_sort(Address *a, int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quick_sort(a, low, pi - 1);
        quick_sort(a, pi + 1, high);
    }
}