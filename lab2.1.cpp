#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<locale.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>

int main() {
    setlocale(LC_ALL, "Ru");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    clock_t start, end, speed;
    int size, r, mult_arr;

    printf("Введите размер массива: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Error");
        return 1;
    }
    int** a = (int**)malloc(size * sizeof(int*));
    int** b = (int**)malloc(size * sizeof(int*));
    int** c = (int**)malloc(size * sizeof(int*));

    if (a == NULL || b == NULL || c == NULL) {
        printf("Error\n");
        return 1;
    }
    for (int i = 0; i < size; i++) {
        a[i] = (int*)malloc(size * sizeof(int));
        b[i] = (int*)malloc(size * sizeof(int));
        c[i] = (int*)malloc(size * sizeof(int));
        if (a[i] == NULL || b[i] == NULL || c[i] == NULL) {
            printf("Error\n");
            return 1;
        }
    }
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            a[i][j] = rand() % 100;
            b[i][j] = rand() % 100;
            c[i][j] = 0;
        }
    }
    start = clock();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            mult_arr = 0;
            for (r = 0; r < size; r++) {
                mult_arr += a[i][r] * b[r][j];
            }
            c[i][j] = mult_arr;
        }
    }
    end = clock();
    speed = end - start;
    for (int i = 0; i < size; i++) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);

    printf("Скорость умножения матриц в секундах:%.3f сек\n", (double)speed / CLOCKS_PER_SEC);
    return 0;
}