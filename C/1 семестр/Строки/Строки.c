/*Все адреса электронной почты в исходной строке заменить на "[контакты запрещены]"*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

char* replace_emails(char*);

int main() {
    setlocale(LC_ALL, "Russian");
    int q = 1, f;
    FILE* in = NULL, * out = NULL;
    char S[255];
    char* S2 = NULL;
    do {
        printf("\nПожалуйста, введите 0, если хотите ввести текст вручную, иначе - любое другое число:\n");
        scanf("%d", &f);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); //В буфере символ новой строки, надо почистить, иначе stdin воспримет его как введённую строку
        if (f == 0) {
            printf("\nПожалуйста, введите текст:\n");
            fgets(S, sizeof(S), stdin);
            S2 = (char*)malloc((strlen(S) + 1) * sizeof(char));
            S2 = replace_emails(S);
            printf("\nПолученный текст:\n");
            printf("%s\n", S2);
        }
        else {
            in = fopen("input.txt", "r");
            if (!in) {
                perror("Ошибка открытия входного файла");
                continue;
            }
            if (fgets(S, sizeof(S), in)) {
                fclose(in);
                S2 = (char*)malloc((strlen(S) + 1) * sizeof(char));
                S2 = replace_emails(S);
                out = fopen("output.txt", "w");
                if (!out) {
                    perror("Ошибка открытия выходного файла");
                    free(S2);
                    continue;
                }
                fprintf(out, "%s", S2);
                fclose(out);
                printf("\nРезультат сохранен в output.txt");
            }
            else {
                perror("Ошибка чтения из файла");
            }
        }
        free(S2);
        printf("\nПожалуйста, введите 0, если хотите выйти из программы, иначе - любое другое число:\n");
        scanf("%d", &q);
    } while (q != 0);
    return 0;
}

char* replace_emails(char* S) {
    int n = 0, c = 0, d = 0, t = 0;
    char* T, * S1, * S2, * S3;
    char s[2] = { 0 };
    S1 = (char*)malloc((strlen(S) + 1) * sizeof(char));
    S2 = (char*)malloc((strlen(S) + 1) * sizeof(char));
    S3 = (char*)malloc((strlen(S) + 1) * sizeof(char));
    strcpy(S1, S);
    T = strtok(S, "`~!@#$%^&*()_+-=:;., №?[]{}/<>|");
    n = strlen(T);
    if (strlen(S1) > 6) {
        while (T != NULL) {
            s[0] = S1[n];
            if (t != 2) {
                strcat(S3, T);
                strcat(S3, s);
            }
            if (S1[n] == '@' && strlen(T) > 1) {
                c = 1;
            }
            else if (S1[n] == '.' && c == 1 && strlen(T) > 1) {
                d = 1;
            }
            else {
                c = 0;
            }
            if (d == 1) {
                t++;
            }
            if (t == 2 && strlen(T) > 1) {
                memset(S3, 0, (strlen(S) + 1));
                strcat(S2, "[контакты запрещены]");
                strcat(S2, s);
                c = 0;
                d = 0;
                t = 0;
            }
            if (c == 0) {
                strcat(S2, S3);
                memset(S3, 0, (strlen(S) + 1));
            }
            T = strtok(NULL, "`~!@#$%^&*()_+-=:;., №?[]{}/<>|");
            if (T != NULL) {
                n += strlen(T) + 1;
            }
        }
    }
    else {
        strcpy(S2, S1);
    }
    free(S1);
    free(S3);
    return S2;
}