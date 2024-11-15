#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Прототипи функцій
void quickSort(int *arr, int low, int high, int *comparisons, int *swaps);
int partition(int *arr, int low, int high, int *comparisons, int *swaps);
void swap(int *a, int *b, int *swaps);
int *read_array_from_file(const char *filename, int *n);
void write_array_to_file(const char *filename, int *arr, int n);

int main() {
    char inputFile[256];
    const char *outputFile = "output.txt";
    int size = 0;
    int comparisons = 0;  // Счётчик сравнений
    int swaps = 0;        // Счётчик обменов

    printf("Введіть ім'я файлу для читання (наприклад, input.txt): ");
    scanf("%255s", inputFile);

    int *arr = read_array_from_file(inputFile, &size);
    if (arr == NULL) {
        printf("Помилка при зчитуванні масиву з файлу.\n");
        return 1;
    }

    clock_t start = clock();  // Початок вимірювання часу
    quickSort(arr, 0, size - 1, &comparisons, &swaps);
    clock_t end = clock();  // Кінець вимірювання часу

    double time_taken = (double)(end - start) * 1000000 / CLOCKS_PER_SEC; // В мікросекундах
    printf("Час виконання сортування: %.2f мкс\n", time_taken);
    printf("Кількість порівнянь: %d\n", comparisons);
    printf("Кількість обмінів: %d\n", swaps);

    // Запис відсортованого масиву в файл
    write_array_to_file(outputFile, arr, size);

    // Звільнення пам'яті
    free(arr);
    return 0;
}

// Реалізація QuickSort з підрахунком порівнянь та обмінів
void quickSort(int *arr, int low, int high, int *comparisons, int *swaps) {
    if (low < high) {
        int pivot = partition(arr, low, high, comparisons, swaps);
        quickSort(arr, low, pivot - 1, comparisons, swaps);
        quickSort(arr, pivot + 1, high, comparisons, swaps);
    }
}

// Функція розподілу з підрахунком порівнянь та обмінів
int partition(int *arr, int low, int high, int *comparisons, int *swaps) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        (*comparisons)++;  // Збільшуємо кількість порівнянь
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j], swaps);
        }
    }
    swap(&arr[i + 1], &arr[high], swaps);
    return (i + 1);
}

// Функція обміну елементів з підрахунком обмінів
void swap(int *a, int *b, int *swaps) {
    int temp = *a;
    *a = *b;
    *b = temp;
    (*swaps)++;  // Збільшуємо кількість обмінів
}

// Читання масиву з файлу без указания размера
int *read_array_from_file(const char *filename, int *n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Помилка при відкриванні файлу.");
        return NULL;
    }

    int capacity = 10;
    int *arr = (int *)malloc(capacity * sizeof(int));
    if (!arr) {
        perror("Помилка виділення пам'яті");
        fclose(file);
        return NULL;
    }

    int value;
    *n = 0;
    while (fscanf(file, "%d", &value) == 1) {
        if (*n >= capacity) {
            capacity *= 2;
            int *temp = realloc(arr, capacity * sizeof(int));
            if (!temp) {
                perror("Помилка перевиділення пам'яті");
                free(arr);
                fclose(file);
                return NULL;
            }
            arr = temp;
        }
        arr[*n] = value;
        (*n)++;
    }

    fclose(file);
    return arr;
}

// Запис масиву в файл
void write_array_to_file(const char *filename, int *arr, int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Помилка при відкриванні файлу.");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}
