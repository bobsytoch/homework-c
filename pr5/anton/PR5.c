#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubbleSort(int arr[], int n, int *comparisons, int *swaps) {
    *comparisons = 0;
    *swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparisons)++;  
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
                (*swaps)++;  
            }
        }
    }
}

void BestCase(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;  
    }
}

void WorstCase(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;  
    }
}
void AverageCase(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;  
    }
}

double measureSortTime(int arr[], int n, int *comparisons, int *swaps) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);  

    bubbleSort(arr, n, comparisons, swaps);

    clock_gettime(CLOCK_MONOTONIC, &end);  
    return ((end.tv_sec - start.tv_sec) * 1000.0) + ((end.tv_nsec - start.tv_nsec) / 1000000.0); 
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n = 100; 
    int arr[n];    
    int comparisons, swaps;  
    double time_taken;  
    srand(time(0));  

    BestCase(arr, n);
    printf("Array before sorting (Best-case):\n");
    printArray(arr, n);
    time_taken = measureSortTime(arr, n, &comparisons, &swaps);
    printf("Array after sorting (Best-case):\n");
    printArray(arr, n);
    printf("Best-case scenario:\nComparisons: %d, Swaps: %d, Time taken: %f milliseconds\n\n", comparisons, swaps, time_taken);

    WorstCase(arr, n);
    printf("Array before sorting (Worst-case):\n");
    printArray(arr, n);
    time_taken = measureSortTime(arr, n, &comparisons, &swaps);
    printf("Array after sorting (Worst-case):\n");
    printArray(arr, n);
    printf("Worst-case scenario:\nComparisons: %d, Swaps: %d, Time taken: %f milliseconds\n\n", comparisons, swaps, time_taken);

    AverageCase(arr, n);
    printf("Array before sorting (Average-case):\n");
    printArray(arr, n);
    time_taken = measureSortTime(arr, n, &comparisons, &swaps);
    printf("Array after sorting (Average-case):\n");
    printArray(arr, n);
    printf("Average-case scenario:\nComparisons: %d, Swaps: %d, Time taken: %f milliseconds\n", comparisons, swaps, time_taken);

    return 0;
}