#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void jSort(int array[], int size) {
    int i, j, minIndex, temp;
    
    for (i = 0; i < size - 1; i++) {
        minIndex = i;
        for (j = i + 1; j < size; j++)
            if (array[j] < array[minIndex]) 
                minIndex = j;
        temp = array[minIndex];
        array[minIndex] = array[i];
        array[i] = temp;
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
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

void testSort(int size) {
    int arr[size];

    // BEST CASE ========
    fillArray(arr, size);
    // /* DEBUG */ printArray(arr, size);
    clock_t start = clock();
    jSort(arr, size);
    clock_t end = clock();
    // /* DEBUG */ printArray(arr, size);
    printf("Best case: %lfms\n", ((double)(end - start)) / 1000 );
    
    // WORST CASE =======
    reverseArray(arr, size);
    // /* DEBUG */ printArray(arr, size);
    start = clock();
    jSort(arr, size);
    end = clock();
    // /* DEBUG */ printArray(arr, size);
    printf("Worst case: %lfms\n", ((double)(end - start)) / 1000 );

    // AVG CASE =======
    shuffleArray(arr, size);
    // /* DEBUG */ printArray(arr, size);
    start = clock();
    jSort(arr, size);
    end = clock();
    // /* DEBUG */ printArray(arr, size);
    printf("Avg. case: %lfms\n", ((double)(end - start)) / 1000 );
}

// Головна функція
int main() {
    int N;

    printf("Enter array length: ");
    scanf("%d", &N);
    if (N < 1) {
        printf("Arrays can't have negative length.");
        return 1;
    }

    testSort(N);

    return 0;
}
