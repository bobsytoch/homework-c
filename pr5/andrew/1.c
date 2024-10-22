#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[], int n, int* comparisons, int* swaps) {
    *comparisons = 0;
    *swaps = 0;
    int swapped;

    for (int i = 0; i < n-1; i++) {
        swapped = 0;
        for (int j = 0; j < n-i-1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j+1]) {
                // Перестановка
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                (*swaps)++;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// Функция для печати массива
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Функция для заполнения массива случайными числами без повторений
void fillArrayRandomUnique(int arr[], int n) {
    int* used = (int*)malloc(1001 * sizeof(int)); // Массив для отслеживания использованных чисел
    if (used == NULL) {
        printf("Не удалось выделить память\n");
        return; 
    }

    for (int i = 0; i < 1001; i++) {
        used[i] = 0; // Инициализируем массив, все числа еще не использованы
    }

    for (int i = 0; i < n; ) {
        int num = rand() % 1001;
        if (used[num] == 0) { // Проверяем, использовалось ли число
            arr[i] = num; 
            used[num] = 1;
            i++;
        }
    }

    free(used); 
}

void fillArrayManual(int arr[], int n) {
    printf("Введите %d целых числа:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}

int main() {
    int comparisons, swaps;
    int n;

    printf("Введите размер массива (макс 1001): ");
    scanf("%d", &n);

    if (n > 1001) {
        printf("Размер должен быть меньше или равен 1001 для уникальных случайных чисел.\n");
        return 1;
    }

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Не удалось выделить память\n");
        return 1; 
    }

    int choice;
    printf("Выберите способ заполнения массива:\n1. Случайные уникальные числа\n2. Ввод вручную\n");
    scanf("%d", &choice);

    if (choice == 1) {
        fillArrayRandomUnique(arr, n);
    } else if (choice == 2) {
        fillArrayManual(arr, n);
    } else {
        printf("Неверный выбор.\n");
        free(arr); 
        return 1;
    }

    printf("Исходный массив: \n");
    printArray(arr, n);

    clock_t start = clock();
    bubbleSort(arr, n, &comparisons, &swaps);
    clock_t end = clock();

    printf("Отсортированный массив: \n");
    printArray(arr, n);

    double time_taken = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
    printf("Время выполнения: %.6f секунд\n", time_taken);
    printf("Сравнения: %d, Перестановки: %d\n", comparisons, swaps);
    free(arr);
    
    return 0;
}
