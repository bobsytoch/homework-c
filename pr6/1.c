#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to keep track of statistics
typedef struct {
    long long comparisons;
    long long swaps;
    long long iterations;
    double time;  // Time taken for sorting
} SortStats;

// Global variables to store statistics
SortStats quicksortStats;
SortStats heapsortStats;

// Function prototypes
void resetStats(SortStats *stats);
void quicksort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void heapsort(int arr[], int n);
void heapify(int arr[], int n, int i);
void testSorts(int arr[], int n);

void resetStats(SortStats *stats) {
    stats->comparisons = 0;
    stats->swaps = 0;
    stats->iterations = 0;
    stats->time = 0.0;  // Reset time
}

// Swap utility function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Quicksort implementation
void quicksort(int arr[], int low, int high) {
    quicksortStats.iterations++;
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        quicksortStats.comparisons++;
        if (arr[j] < pivot) {
            i++;
            quicksortStats.swaps++;
            swap(&arr[i], &arr[j]);
        }
    }
    quicksortStats.swaps++;
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Heapsort implementation
void heapsort(int arr[], int n) {
    heapsortStats.iterations++;

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i >= 0; i--) {
        heapsortStats.swaps++;
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void heapify(int arr[], int n, int i) {
    heapsortStats.iterations++;
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    heapsortStats.comparisons++;
    if (left < n && arr[left] > arr[largest])
        largest = left;

    heapsortStats.comparisons++;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        heapsortStats.swaps++;
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void shuffleArray(int arr[], int n) {
    // Seed the random number generator
    srand(time(0));

    for (int i = n - 1; i > 0; i--) {
        // Generate a random index between 0 and i
        int j = rand() % (i + 1);

        // Swap arr[i] with arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// Helper function to print array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Test function to measure performance
void testSorts(int arr[], int n) {
    int *arrCopy = (int *)malloc(n * sizeof(int));

    // Test Quicksort
    for (int i = 0; i < n; i++)
        arrCopy[i] = arr[i];

    resetStats(&quicksortStats);
    clock_t start = clock();  // Start timing
    quicksort(arrCopy, 0, n - 1);
    clock_t end = clock();  // End timing
    quicksortStats.time = (double)(end - start) / CLOCKS_PER_SEC * 1000000;  // Calculate time

    printf("Quicksort - Comparisons: %lld, Swaps: %lld, Iterations: %lld, Time: %.6f us\n",
           quicksortStats.comparisons, quicksortStats.swaps, quicksortStats.iterations, quicksortStats.time);

    // Test Heapsort
    for (int i = 0; i < n; i++) arrCopy[i] = arr[i];

    resetStats(&heapsortStats);
    start = clock();  // Start timing
    heapsort(arrCopy, n);
    end = clock();  // End timing
    heapsortStats.time = (double)(end - start) / CLOCKS_PER_SEC * 1000000;  // Calculate time

    printf("Heapsort - Comparisons: %lld, Swaps: %lld, Iterations: %lld, Time: %.6f us\n",
           heapsortStats.comparisons, heapsortStats.swaps, heapsortStats.iterations, heapsortStats.time);

    free(arrCopy);
}

// Main function to test worst, best, and average cases
int main() {
    int n;
    printf("Enter number bitch: ");
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i; // Отсортированный массив
    }

    // Best case: sorted array
    printf("Best Case (sorted array):\n");
    testSorts(arr, n);

    // Worst case: reversed array
    for (int i = 0; i < n; i++) {
        int a = arr[n - i];
        arr[n - i] = arr[n];
        arr[n] = a;
    }
    printf("\nWorst Case (reversed array):\n");
    testSorts(arr, n);

    // Average case: random array
    shuffleArray(arr, n);
    printf("\nAverage Case (random array):\n");
    testSorts(arr, n);

    return 0;
}
