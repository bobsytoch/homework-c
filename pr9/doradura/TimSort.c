#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_RUN 32

// Прототипи функцій
void timSort(int *arr, int n);
void insertionSort(int *arr, int left, int right);
void merge(int *arr, int left, int mid, int right);
int *read_array_from_file(const char *filename, int *n);
void write_array_to_file(const char *filename, int *arr, int n);

// Глобальные переменные для подсчета сравнений и обменов
int comparisons = 0;
int swaps = 0;

int main() {
    char inputFile[256];
    const char *outputFile = "output.txt";
    int size = 0;

    printf("Введіть ім'я файлу для читання (наприклад, input.txt): ");
    scanf("%255s", inputFile);

    int *arr = read_array_from_file(inputFile, &size);
    if (arr == NULL) {
        printf("Помилка при зчитуванні масиву з файлу.\n");
        return 1;
    }

    clock_t start = clock();  // Початок вимірювання часу
    timSort(arr, size);
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

// Реалізація TimSort
void timSort(int *arr, int n) {
    // Сортування частин масиву методом вставки
    for (int i = 0; i < n; i += MIN_RUN) {
        insertionSort(arr, i, (i + MIN_RUN - 1 < n - 1) ? (i + MIN_RUN - 1) : (n - 1));
    }

    // Слияние отсортированных подмассивов
    for (int size = MIN_RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

// Функція вставки для сортування маленьких діапазонів
void insertionSort(int *arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            comparisons++;  // Увеличиваем счетчик сравнений
            arr[j + 1] = arr[j];
            swaps++;  // Увеличиваем счетчик обменов
            j--;
        }
        comparisons++;  // Сравнение, когда цикл завершен
        arr[j + 1] = temp;
        if (j + 1 != i) swaps++;  // Увеличиваем счетчик обменов, если было перемещение
    }
}

// Злиття для двох відсортованих частин масиву
void merge(int *arr, int left, int mid, int right) {
    int len1 = mid - left + 1, len2 = right - mid;
    int *leftArr = (int *)malloc(len1 * sizeof(int));
    int *rightArr = (int *)malloc(len2 * sizeof(int));

    for (int i = 0; i < len1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < len2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        comparisons++;  // Увеличиваем счетчик сравнений
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < len2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    free(leftArr);
    free(rightArr);
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
