#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int arr[], int size) {
    printf("[ ");
    for (int i = 0; i < size-1; i++) 
        printf("%d, ", arr[i]);
    printf("%d ]\n", arr[size-1]);
}

void fillArray(int arr[], int size) {
    for (int i = 0; i < size; i++) arr[i] = i + 1;
}

void reverseArray(int arr[], int size) {
    for (int i = 0; i < size / 2; i++) 
    {
        int temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}

void shuffleArray(int arr[], int size) {
    srand(time(0));
    for (int i = size - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1); 
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void shellGaps(int gaps[], int gapCount, int arraySize) {
    int i = 0;
    for (int g = arraySize / 2; g >= 1 && i < gapCount; i++, g /= 2) 
    {
        gaps[i] = g;
    }

    // this is to fill excess space in the array
    if (i < gapCount - 1) for (; i < gapCount; i++) gaps[i] = 0;
}

int ciura[] = { 1, 4, 10, 23, 57, 132, 301, 701 };
void ciuraGaps(int gaps[], int gapCount, int arraySize) {
    for (int i = 0; i  < gapCount; i++) 
        gaps[gapCount-i-1] = i < 9 ? ciura[i] : 0;
}

void shellSort(int array[], int size, int gaps[], int gapCount) {
    for (int gapIndex = 0; gapIndex < gapCount; gapIndex++) 
    {
        int gap = gaps[gapIndex];
        // gap optimization
        if (gap >= size || gap < 1) continue;

        for (int i = 0; i < size; i+= gap)
        {
            // insertion sort for the subarray
            int key = array[i];
            int j = i - gap;

            while (j >= 0 && array[j] > key) {
                // /* DEBUG */printf("%d %d %d\n", gap, i, j);
                array[j + gap] = array[j];
                j = j - gap;
            }
            array[j + gap] = key;
        }
    }
}

void testSort(int arr[], int N, int gaps[], int gapCount) {
    // BEST CASE ========
    fillArray(arr, N);
    // /* DEBUG */ printArray(arr, size);
    clock_t start = clock();
    shellSort(arr, N, gaps, gapCount);
    clock_t end = clock();
    // /* DEBUG */ printArray(arr, size);
    printf("Best case: %lfms\n", ((double)(end - start)) / 1000 );

    // WORST CASE =======
    reverseArray(arr, N);
    // /* DEBUG */ printArray(arr, size);
    start = clock();
    shellSort(arr, N, gaps, gapCount);
    end = clock();
    // /* DEBUG */ printArray(arr, size);
    printf("Worst case: %lfms\n", ((double)(end - start)) / 1000 );

    // AVG CASE =======
    shuffleArray(arr, N);
    // /* DEBUG */ printArray(arr, size);
    start = clock();
    shellSort(arr, N, gaps, gapCount);
    end = clock();
    // /* DEBUG */ printArray(arr, size);
    printf("Avg. case: %lfms\n", ((double)(end - start)) / 1000 );
}

int main() {
    int N = 4000;
    // printf("Enter array length: ");
    // scanf("%d", &N);
    // if (N < 1) {
    //     printf("Arrays can't have negative length.");
    //     return 1;
    // }
    printf("Array size: %d\n", N);

    int arr[N];
    
    int sGapsLength = (int)log2(N);
    int sGaps[sGapsLength];

    int cGaps[8];

    // 1 - SHELL GAPS
    printf("SHELL'S ORIGINAL GAPS: \n");
    shellGaps(sGaps, sGapsLength, N);
    testSort(arr, N, sGaps, sGapsLength);

    // 2 - CIURA GAPS
    printf("CIURA'S GAPS: \n");
    ciuraGaps(cGaps, 8, N);
    testSort(arr, N, sGaps, sGapsLength);

    return 0;
}