#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  // Для QueryPerformanceCounter

void swap(int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n, int* comparisons, int* swaps) {
    int i, j;
    bool swapped;
    *comparisons = 0;  // Лічильник порівнянь
    *swaps = 0;        // Лічильник перестановок

    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            (*comparisons)++;  // Збільшуємо лічильник порівнянь
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                (*swaps)++;     // Збільшуємо лічильник перестановок
                swapped = true;
            }
        }
        if (!swapped) // Якщо не було перестановок, масив відсортовано
            break;
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int comparisons, swaps;

    int* arr = NULL;
    int num;
    int count = 0;

    printf("Введіть числа для масиву (введіть 0 для завершення):\n");
    while (1) {
        scanf("%d", &num);

        // Якщо ввели 0, завершуємо введення
        if (num == 0)
            break;

        // Збільшуємо розмір масиву на 1 елемент
        arr = (int*)realloc(arr, (count + 1) * sizeof(int));
        if (arr == NULL) {
            perror("Не вдалося виділити пам'ять");
            exit(EXIT_FAILURE);
        }

        // Додаємо новий елемент у масив
        arr[count] = num;
        count++;
    }

    LARGE_INTEGER start, end, frequency;

    QueryPerformanceFrequency(&frequency); // Отримуємо частоту таймера
    QueryPerformanceCounter(&start);       // Початок вимірювання часу

    bubbleSort(arr, count, &comparisons, &swaps);

    QueryPerformanceCounter(&end);         // Кінець вимірювання часу

    double time_us = (double)(end.QuadPart - start.QuadPart) * 1000000.0 / frequency.QuadPart; // Час у мікросекундах

    printf("\nВідсортований масив: \n");
    printArray(arr, count);

    printf("\nЧас сортування: %f мкс\n", time_us);
    printf("Кількість порівнянь: %d\n", comparisons);
    printf("Кількість перестановок: %d\n", swaps);

    // Звільняємо пам'ять
    free(arr);
    
    return 0;
}
