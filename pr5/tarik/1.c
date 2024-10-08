#include <stdio.h>
#include <time.h>

void bubbleSort(int arr[], int n, int* c, int* s) {
    int swapped; *c = 0; *s = 0;
    
    for (int i = 0; i < n-1; i++) {
        swapped = 0;
        for (int j = 0; j < n-i-1; j++) {
            (*c)++;
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                (*s)++;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    int comparisons, swaps;

    int n;
    printf("Enter array length: ");
    scanf("%d", &n);

    printf("Enter array elements (separated by whitespace): ");
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    clock_t t = clock();
    bubbleSort(arr, n, &comparisons, &swaps);
    t = clock() - t;

    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    double time_taken = ((double) t) * 1000 / CLOCKS_PER_SEC;
    printf("Time taken: %.3fms\n", time_taken);
    printf("Comparisons: %d, Swaps: %d\n", comparisons, swaps);

    return 0;
}
