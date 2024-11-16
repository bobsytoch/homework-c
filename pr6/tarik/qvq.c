#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int arr[], int low, int high) {
	int p = arr[low], i = low, j = high;

	while (i < j) {
		while (arr[i] <= p && i <= high - 1) i++;
		while (arr[j] > p && j >= low + 1) j--;
		if (i < j) swap(&arr[i], &arr[j]);
	}
  
	swap(&arr[low], &arr[j]);
	return j;
}

void quicksort(int arr[], int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quicksort(arr, low, pi - 1);
		quicksort(arr, pi + 1, high);
	}
}

int compare(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

void fillArray(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = i + 1;  
	}
}

void printArray(int arr[], int size) {
	printf("[");
	for (int i = 0; i < size; i++) {
		printf("%d", arr[i]);
		if (i < size - 1)  printf(", ");
	}
	printf("]\n");
}

int main() {
	int arr[100000];
	fillArray(arr, 100000);

	clock_t s = clock();
	quicksort(arr, 0, 99999);
	clock_t e = clock();

	printf("%lf\n", ((double) e - s) / CLOCKS_PER_SEC);

	fillArray(arr, 100000);
	s = clock();
	qsort(arr, 100000, sizeof(int), compare);
	e = clock();

	printf("%lf\n", ((double) e - s) / CLOCKS_PER_SEC);
	return 0;
}