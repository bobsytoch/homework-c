#include <stdio.h>
#include <time.h>

// Функція для сортування масиву методом бульбашки
void bubbleSort(int arr[], int n, int* comparisons, int* swaps) {
    *comparisons = 0;
    *swaps = 0;
    int swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j + 1]) {
                // Виконати обмін
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*swaps)++;
                swapped = 1;
            }
        }
        // Якщо на якомусь етапі не було жодного обміну, масив уже відсортовано
        if (!swapped) {
            break;
        }
    }
}

// Функція для виводу масиву
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int comparisons, swaps, n;

    // Введення розміру масиву
    printf("Введіть кількість елементів масиву: ");
    scanf("%d", &n);

    int arr[n];

    // Введення елементів масиву вручну
    printf("Введіть %d елементів масиву:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Оригінальний масив: \n");
    printArray(arr, n);

    clock_t start = clock(); // Початок вимірювання часу
    bubbleSort(arr, n, &comparisons, &swaps);
    clock_t end = clock();   // Кінець вимірювання часу

    printf("Відсортований масив: \n");
    printArray(arr, n);

    double timeTaken = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC; // Розрахунок часу
    printf("Час виконання: %.6f мiлiсекунд\n", timeTaken);
    printf("Порівняння: %d, Обміни: %d\n", comparisons, swaps);

    return 0;
}
