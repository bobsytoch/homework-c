#include <stdio.h>
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
        // Якщо на деякому етапі не було жодної перестановки, то масив уже відсортований
        if (!swapped) {
            break;
        }
    }
}

// Функція для друку масиву
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int comparisons, swaps;

    // Масив для сортування
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);

    clock_t start = clock();
    bubbleSort(arr, n, &comparisons, &swaps);
    clock_t end = clock();

    printf("Sorted array: \n");
    printArray(arr, n);

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %.6f seconds\n", time_taken);
    printf("Comparisons: %d, Swaps: %d\n", comparisons, swaps);

    return 0;
}
