#include <stdio.h>

// Функция сортировки пузырьком по возрастанию
int bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Меняем элементы местами
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

    printf("Введите количество гвоздей: ");
    scanf("%d", &N);

    int a[N];
    int d[N];

    printf("Введите координаты гвоздей:\n");
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    // Сортируем массив координат по возрастанию
    int res = bubbleSort(a, N);
    if (!res) return printf("Не может быть гвоздей с одинаковыми координатами.\n");

    // Инициализация начальных значений
    d[0] = 0;
    d[1] = a[1] - a[0]; // Для второго гвоздя длина — расстояние до первого
    d[N-2] = 0;

    printf("%d %d %d\n", d[0], d[1], d[N-1]);
    // Вычисляем минимальные расстояния для всех гвоздей
    for (int i = 2; i < N - 2; i++) {
        int x = a[i + 1] - a[i];
        int y = a[i] - a[i - 1];

        if (x < y || (x == y && d[i-1])) { 
            d[i] = 0; 
            d[i + 1] = x; 
        }
        else if (x > y || (x == y && !d[i-1])) {
            d[i] = y;
        }

        printf("%d | %d %d %d | %d %d\n", i, a[i-1], a[i], a[i+1], d[i], d[i+1]);
    }

    d[N-1] = a[N-1] - a[N-2];

    // Вывод минимальной суммарной длины ниточек
    int sum = 0;
    for(int i = 0; i < N; i++) {
        sum += d[i];
    }

    printf("Минимальная суммарная длина ниточек: %d\n", sum);

    return 0;
}
