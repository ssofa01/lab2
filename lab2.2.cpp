
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<locale.h>
#include <string.h>

void shell(int* items, int count)
{
    int i, j, gap, k;
    int x, a[5];
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;
    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right)
{
    int i, j;
    int x, y;
    i = left; j = right;
    x = items[(left + right) / 2];
    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;
        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);
    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void randomm(int* items, int size) {
    for (int i = 0; i < size; i++)
        items[i] = rand() % 100 + 1;
}

void vozr(int* items, int size) {
    for (int i = 0; i < size; i++)
        items[i] = i;
}

void ub(int* items, int size) {
    for (int i = 0; i < size; i++)
        items[i] = size - i;
}

void vozr_ub(int* items, int size) {
    for (int i = 0; i < size / 2; i++)
        items[i] = i;
    for (int i = size / 2; i < size; i++)
        items[i] = size - 1 - (i - size / 2);
}

double timeShell(int* items, int* copy, int size) {
    memcpy(copy, items, size * sizeof(int));
    clock_t s = clock();
    shell(copy, size);
    clock_t e = clock();
    return (double)(e - s) / CLOCKS_PER_SEC;
}

double timeQs(int* items, int* copy, int size) {
    memcpy(copy, items, size * sizeof(int));
    clock_t s = clock();
    qs(copy, 0, size - 1);
    clock_t e = clock();
    return (double)(e - s) / CLOCKS_PER_SEC;
}

double timeQSort(int* items, int* copy, int size) {
    memcpy(copy, items, size * sizeof(int));
    clock_t s = clock();
    qsort(copy, size, sizeof(int), cmp);
    clock_t e = clock();
    return (double)(e - s) / CLOCKS_PER_SEC;
}

void printRow(const char* name, int* items, int* copy, int size) {
    double t1 = timeShell(items, copy, size);
    double t2 = timeQs(items, copy, size);
    double t3 = timeQSort(items, copy, size);
    printf("| %-25s | %12.9f | %12.9f | %12.9f |\n", name, t1, t2, t3);
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Ru");

    srand((unsigned)time(NULL));
    int size;

    printf("Введите размер массива: ");
    if (scanf_s("%d", &size) != 1 || size <= 0) {
        printf("Некорректный размер\n");
        return 1;
    }

    int* items = (int*)malloc(size * sizeof(int));
    int* copy = (int*)malloc(size * sizeof(int));

    if (items == NULL || copy == NULL) {
        printf("Ошибка выделения памяти\n");
        free(items);
        free(copy);
        return 1;
    }

    printf("\n--------------------------------------------------------------------------\n");
    printf("| %-25s | %-12s | %-12s | %-12s |\n",
        "Тип массива", "shell", "qs", "qsort");
    printf("--------------------------------------------------------------------------\n");

    randomm(items, size);
    printRow("Случайный", items, copy, size);

    vozr(items, size);
    printRow("Возрастающий", items, copy, size);

    ub(items, size);
    printRow("Убывающий", items, copy, size);

    vozr_ub(items, size);
    printRow("Возрастающе-убывающий", items, copy, size);

    printf("--------------------------------------------------------------------------\n");

    free(items);
    free(copy);
    return 0;
}
