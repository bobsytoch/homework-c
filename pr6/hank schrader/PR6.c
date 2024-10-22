#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Глобальні змінні для підрахунку порівнянь та перестановок
int comparisons = 0;
int swaps = 0;

// Функція для обміну двох елементів масиву
void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    swaps++;  // Збільшуємо кількість перестановок
}

// Функція, яка розбиває масив на дві частини навколо опорного елемента p
int Partition(int arr[], int low, int high) {
    int p = arr[low];
    int i = low;
    int j = high;

    while (i < j) {
        // Знаходить елемент більший за pivot зліва
        while (arr[i] <= p && i < high) {
            i++;
            comparisons++;  // Збільшуємо кількість порівнянь
        }
        // Знаходить елемент менший за pivot справа
        while (arr[j] > p && j > low) {
            j--;
            comparisons++;  // Збільшуємо кількість порівнянь
        }
        // Міняє місцями елементи, якщо індекси не перетнулися
        if (i < j) {
            Swap(&arr[i], &arr[j]);
        }
    }
    // Поміщає опорний елемент на правильну позицію
    Swap(&arr[low], &arr[j]);
    return j;
}

// Функція швидкого сортування
void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        // Розбиває масив і отримує індекс опорного елемента
        int pi = Partition(arr, low, high);
        // Рекурсивно сортує ліву та праву частини масиву
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

// Функція, яка будує купу
void Heapify(int arr[], int n, int i) {
    int largest = i; // Ініціалізація найбільшого елементу як корінь
    int l = 2 * i + 1; // Лівий нащадок
    int r = 2 * i + 2; // Правий нащадок

    // Якщо лівий нащадок більший за корінь
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    comparisons++;  // Збільшуємо кількість порівнянь

    // Якщо правий нащадок більший за найбільший елемент
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
    comparisons++;  // Збільшуємо кількість порівнянь

    // Якщо найбільший елемент не корінь, міняємо місцями та рекурсивно викликаємо Heapify
    if (largest != i) {
        Swap(&arr[i], &arr[largest]);
        Heapify(arr, n, largest);
    }
}

// Функція сортування купою
void HeapSort(int arr[], int n) {
    // Побудова Heapify з масиву
    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(arr, n, i);
    }
    // Один за одним витягує елементи з купи
    for (int i = n - 1; i > 0; i--) {
        Swap(&arr[0], &arr[i]);
        Heapify(arr, i, 0);
    }
}

// Масив відсортований за зростанням
void BestCase(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

// Масив відсортований рандомно
void AverageCase(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }
}

// Масив відсортований за спаданням
void WorstCase(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

// Функція запитує у користувача новий розмір масиву, зчитує введене значення та повертає його
int SizeArr() {
    int new_size;
    printf("Введіть новий розмір масиву: ");
    scanf("%d", &new_size);
    printf("Розмір масиву змінено на %d.\n", new_size);
    return new_size;
}

int main() {
    int n, choice;

    printf("Введіть початковий розмір масиву: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));

    do {
        printf("\n--- Меню ---\n");
        printf("1. QuickSort (всі кейси)\n");
        printf("2. HeapSort (всі кейси)\n");
        printf("3. Змінити розмір масиву\n");
        printf("4. Вийти\n");
        printf("Введіть свій вибір: ");
        scanf("%d", &choice);

        clock_t start, end;
        double time_taken;

        switch (choice) {
            case 1:
                comparisons = 0;  // Очищаємо лічильники
                swaps = 0;

                BestCase(arr, n);
                start = clock();
                QuickSort(arr, 0, n - 1);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;
                printf("Best-case QuickSort: Час сортування: %f мікросекунд\n", time_taken);
                printf("Порівнянь: %d, Перестановок: %d\n", comparisons, swaps);

                comparisons = 0;  // Очищаємо лічильники
                swaps = 0;

                AverageCase(arr, n);
                start = clock();
                QuickSort(arr, 0, n - 1);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;
                printf("Average-case QuickSort: Час сортування: %f мікросекунд\n", time_taken);
                printf("Порівнянь: %d, Перестановок: %d\n", comparisons, swaps);

                comparisons = 0;  // Очищаємо лічильники
                swaps = 0;

                WorstCase(arr, n);
                start = clock();
                QuickSort(arr, 0, n - 1);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;
                printf("Worst-case QuickSort: Час сортування: %f мікросекунд\n", time_taken);
                printf("Порівнянь: %d, Перестановок: %d\n", comparisons, swaps);

                break;

            case 2:
                comparisons = 0;  // Очищаємо лічильники
                swaps = 0;

                BestCase(arr, n);
                start = clock();
                HeapSort(arr, n);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;
                printf("Best-case HeapSort: Час сортування: %f мікросекунд\n", time_taken);
                printf("Порівнянь: %d, Перестановок: %d\n", comparisons, swaps);
                
                comparisons = 0;  // Очищаємо лічильники
                swaps = 0;

                AverageCase(arr, n);
                start = clock();
                HeapSort(arr, n);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;
                printf("Average-case HeapSort: Час сортування: %f мікросекунд\n", time_taken);
                printf("Порівнянь: %d, Перестановок: %d\n", comparisons, swaps);
 
                comparisons = 0;  // Очищаємо лічильники
                swaps = 0;

                WorstCase(arr, n);
                start = clock();
                HeapSort(arr, n);
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;
                printf("Worst-case HeapSort: Час сортування: %f мікросекунд\n", time_taken);
                printf("Порівнянь: %d, Перестановок: %d\n", comparisons, swaps);

                break;

            case 3:
                n = SizeArr();
                arr = (int *)realloc(arr, n * sizeof(int));
                break;

            case 4:
                printf("Вихід з програми...\n");
                break;

            default:
                printf("Невірний вибір! Спробуйте ще раз.\n");
                break;
        }
    } while (choice != 4);
    free(arr);
    return 0;
}
