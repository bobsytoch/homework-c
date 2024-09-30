#include <stdio.h>

// Функція сортування пузирком по зростанню
int bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Міняємо елементи місцями
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
       		else if (arr[j] == arr[j+1]) return 0;
        }
    }
	return 1;
}

int main() {
    int N;

    printf("Введіть кількість цвяхів: ");
    scanf("%d", &N);

    int a[N];
    int d[N];

    printf("Введіть координати цвяхів: ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    // Сортуємо масив координат за зростанням
    int result = bubbleSort(a, N);
    if (!result) return printf("Не може бути цвяхів з однаковими координатами.\n");

    // Ініціалізація початкових значень
    d[0] = 0;
    d[1] = a[1] - a[0];
     d[N-2] = 0;

    // Обчислюємо мінімальні відстані для всіх цвяхів
    for (int i = 2; i < N - 2; i++) {
        int distanceToNext = a[i + 1] - a[i];
        int distanceToPrev = a[i] - a[i - 1];

        if (distanceToNext < distanceToPrev || distanceToNext == distanceToPrev && d[i-1]) { 
            d[i] = 0; 
            d[i + 1] = distanceToNext; 
        }
        else if (distanceToNext > distanceToPrev || distanceToNext == distanceToPrev && !d[i-1]){
            d[i] = distanceToPrev;
        }
    }

	d[N-1] = a[N-1] - a[N-2];

    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += d[i];
    }

    printf("Мінімальна сумарна довжина ниточок: %d\n", sum);

    return 0;
}
