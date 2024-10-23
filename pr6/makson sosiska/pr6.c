#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Структура для зберігання статистики сортування
typedef struct {
    long long comparisonCount; // Кількість порівнянь
    long long swapCount;       // Кількість обмінів
    long long iterationCount;   // Кількість ітерацій
    double elapsedTime;        // Час, витрачений на сортування
} SortMetrics;

// Глобальні змінні для статистики
SortMetrics quickMetrics;
SortMetrics heapMetrics;

// Прототипи функцій
void clearMetrics(SortMetrics *metrics);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);
void runSortingTests(int arr[], int n);
void shuffle(int arr[], int n);

void clearMetrics(SortMetrics *metrics) {
    metrics->comparisonCount = 0;
    metrics->swapCount = 0;
    metrics->iterationCount = 0;
    metrics->elapsedTime = 0.0;  // Скидання часу
}

// Функція для обміну елементів
void swapElements(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Реалізація швидкого сортування
void quickSort(int arr[], int low, int high) {
    quickMetrics.iterationCount++;
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivotValue = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        quickMetrics.comparisonCount++;
        if (arr[j] < pivotValue) {
            i++;
            quickMetrics.swapCount++;
            swapElements(&arr[i], &arr[j]);
        }
    }
    quickMetrics.swapCount++;
    swapElements(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Реалізація купчастого сортування
void heapSort(int arr[], int n) {
    heapMetrics.iterationCount++;

    // Побудова купи
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Витягування елементів з купи
    for (int i = n - 1; i >= 0; i--) {
        heapMetrics.swapCount++;
        swapElements(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int i) {
    heapMetrics.iterationCount++;
    int largest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n) {
        heapMetrics.comparisonCount++;
        if (arr[leftChild] > arr[largest])
            largest = leftChild;
    }

    if (rightChild < n) {
        heapMetrics.comparisonCount++;
        if (arr[rightChild] > arr[largest])
            largest = rightChild;
    }

    if (largest != i) {
        heapMetrics.swapCount++;
        swapElements(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void shuffle(int arr[], int n) {
    srand((unsigned int)time(NULL)); // Випадкове насіння

    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swapElements(&arr[i], &arr[j]);
    }
}

// Функція для тестування сортувань
void runSortingTests(int arr[], int n) {
    int *tempArr = (int *)malloc(n * sizeof(int));

    // Тест швидкого сортування
    for (int i = 0; i < n; i++)
        tempArr[i] = arr[i];

    clearMetrics(&quickMetrics);
    clock_t start = clock();  // Початок вимірювання часу
    quickSort(tempArr, 0, n - 1);
    clock_t end = clock();    // Кінець вимірювання часу
    quickMetrics.elapsedTime = (double)(end - start) / CLOCKS_PER_SEC * 1000000;  // Час у мікросекундах

    printf("Швидке Сортування - Порівняння: %lld, Обміни: %lld, Ітерації: %lld, Час: %.6f мкс\n",
           quickMetrics.comparisonCount, quickMetrics.swapCount, quickMetrics.iterationCount, quickMetrics.elapsedTime);

    // Тест купчастого сортування
    for (int i = 0; i < n; i++) 
        tempArr[i] = arr[i];

    clearMetrics(&heapMetrics);
    start = clock();  // Початок вимірювання часу
    heapSort(tempArr, n);
    end = clock();    // Кінець вимірювання часу
    heapMetrics.elapsedTime = (double)(end - start) / CLOCKS_PER_SEC * 1000000;  // Час у мікросекундах

    printf("Купчасте Сортування - Порівняння: %lld, Обміни: %lld, Ітерації: %lld, Час: %.6f мкс\n",
           heapMetrics.comparisonCount, heapMetrics.swapCount, heapMetrics.iterationCount, heapMetrics.elapsedTime);

    free(tempArr);
}

// Основна функція для тестування
int main() {
    int n;
    printf("Введіть кількість елементів: ");
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i; // Відсортований масив
    }

    // Найкращий випадок: відсортований масив
    printf("Найкращий Випадок (відсортований масив):\n");
    runSortingTests(arr, n);

    // Найгірший випадок: обернений масив
    for (int i = 0; i < n / 2; i++) {
        swapElements(&arr[i], &arr[n - 1 - i]);
    }
    printf("\nНайгірший Випадок (обернений масив):\n");
    runSortingTests(arr, n);

    // Середній випадок: випадковий масив
    shuffle(arr, n);
    printf("\nСередній Випадок (випадковий масив):\n");
    runSortingTests(arr, n);

    return 0;
}
