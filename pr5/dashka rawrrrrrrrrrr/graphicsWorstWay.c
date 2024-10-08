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

int main() {
    int comparisons, swaps;
    double times[1500 / 100 + 1]; // Для збереження часу виконання
    int count;

    printf("Розмір масиву\tЧас виконання (мкс)\n");

    // Збираємо дані для масивів від 100 до 1500 елементів
    for (count = 100; count <= 1500; count += 100) {
        int* arr = (int*)malloc(count * sizeof(int));

        // Заповнюємо масив у зворотному порядку (найгірший випадок)
        for (int i = 0; i < count; i++) {
            arr[i] = count - i;  // Відсортований у зворотному порядку
        }

        LARGE_INTEGER start, end, frequency;
        QueryPerformanceFrequency(&frequency); // Отримуємо частоту таймера
        QueryPerformanceCounter(&start);       // Початок вимірювання часу

        bubbleSort(arr, count, &comparisons, &swaps); // Викликаємо функцію сортування

        QueryPerformanceCounter(&end);         // Кінець вимірювання часу

        // Час у мікросекундах
        times[(count / 100) - 1] = (double)(end.QuadPart - start.QuadPart) * 1000000.0 / frequency.QuadPart;
        
        // Виводимо результати для кожного розміру
        printf("%d\t\t%f\n", count, times[(count / 100) - 1]);

        free(arr); // Звільняємо пам'ять
    }

    return 0;
}
