#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int swaps = 0,
    comparisons = 0;

void swap(int* a, int* b) { int temp = *a; *a = *b; *b = temp; }

// HEAPSORT
void heapify(int arr[], int n, int i) {
    int largest = i, 
        left = 2 * i + 1, 
        right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right; 
    if (largest != i) { swap(&arr[i], &arr[largest]); heapify(arr, n, largest); }
}
void heapsort(int arr[], int n) { 
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) { swap(&arr[0], &arr[i]); heapify(arr, i, 0); }
}

// QUICKSORT
int partition(int arr[], int low, int high) {
	int p = arr[low], 
        i = low, 
        j = high;

	while (i < j) {
		while (arr[i] <= p && i <= high - 1) i++;
		while (arr[j] > p && j >= low + 1) j--;
		if (i < j) swap(&arr[i], &arr[j]);
	}
  
	swap(&arr[low], &arr[j]);
	return j;
}
void quicksort(int arr[], int low, int high) {
	if (low > high) return;
    int p = partition(arr, low, high);
	quicksort(arr, low, p - 1);
	quicksort(arr, p + 1, high);
}

// ARRAY FUNCTIONS
void fillArray(int array[], int size) { for (int i = 0; i < size; i++) array[i] = i + 1; }
void reverseArray(int array[], int size) {
    for (int i = 0; i < size / 2; i++) {
        int temp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = temp;
    }
}
void shuffleArray(int array[], int size) {
    srand(time(NULL));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

int main() {
    int n;
    printf("Введіть довжину масиву: ");
    scanf("%d", &n);

    int arr[n];
    // TESTING QUICKSORT
	fillArray(arr, n);

	clock_t s = clock();
	quicksort(arr, 0, n);
	clock_t e = clock();
	printf("%lf\n", ((double) e - s) / CLOCKS_PER_SEC);
    
    reverseArray(arr, n);
    s = clock();
	quicksort(arr, 0, n);
	e = clock();
	printf("%lf\n", ((double) e - s) / CLOCKS_PER_SEC);

    shuffleArray(arr, n);
    s = clock();
	quicksort(arr, 0, n);
	e = clock();
	printf("%lf\n", ((double) e - s) / CLOCKS_PER_SEC);

    // TESTING HEAPSORT
    fillArray(arr, n);

	s = clock();
	heapsort(arr, n);
	e = clock();
	printf("%lf\n", ((double) e - s) / CLOCKS_PER_SEC);
    
    reverseArray(arr, n);
    s = clock();
	heapsort(arr, n);
	e = clock();
	printf("%lf\n", ((double) e - s) / CLOCKS_PER_SEC);

    shuffleArray(arr, n);
    s = clock();
	heapsort(arr, n);
	e = clock();
	printf("%lf\n", ((double) e - s) / CLOCKS_PER_SEC);

	return 0;
}