#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Функція для сортування методом Дженсена
void j_sort(int *arr, int n, int *comparisons, int *swaps) {
    int j = n / 2; // Початкова відстань для порівняння

    while (j > 0) {
        bool sorted = true; // Перевірка на відсутність обмінів

        for (int i = 0; i + j < n; i++) {
            (*comparisons)++; // Ураховуємо кожне порівняння, коли воно необхідне

            if (arr[i] > arr[i + j]) {
                int temp = arr[i];
                arr[i] = arr[i + j];
                arr[i + j] = temp;
                (*swaps)++; // Ураховуємо перестановку
                sorted = false; // Вказуємо, що відбувся обмін, отже, не повністю відсортовано
            }
        }

        if (sorted) break; // Завершуємо, якщо не було обмінів
        j /= 2; // Зменшуємо відстань j вдвічі
    }
}

// Функція для зчитування масиву з файлу
int *read_array_from_file(const char *filename, int *n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Помилка при відкриванні файлу.");
        return NULL;
    }

    int size = 10; // Початковий розмір масиву
    int *arr = (int *)malloc(size * sizeof(int));
    if (!arr) {
        perror("Помилка виділення пам'яті");
        fclose(file);
        return NULL;
    }

    *n = 0;
    while (fscanf(file, "%d", &arr[*n]) == 1) { // Читаємо числа до кінця файлу
        (*n)++;
        if (*n >= size) { // Збільшуємо розмір масиву за необхідності
            size *= 2;
            arr = (int *)realloc(arr, size * sizeof(int));
            if (!arr) {
                perror("Помилка при перевиділенні пам'яті");
                fclose(file);
                return NULL;
            }
        }
    }
    fclose(file);

    return arr;
}

// Функція для запису масиву у файл
void write_array_to_file(const char *filename, int *arr, int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Помилка при відкриванні файлу.");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}

// Головна функція програми
int main() {
    char input_filename[100];
    int n;

    printf("Введіть назву файлу для зчитування: ");
    scanf("%99s", input_filename);

    int *arr = read_array_from_file(input_filename, &n);
    if (arr == NULL) {
        return 1;
    }

    int comparisons = 0; // Змінна для підрахунку кількості порівнянь
    int swaps = 0; // Змінна для підрахунку кількості перестановок

    clock_t start, end;
    start = clock();
    
    j_sort(arr, n, &comparisons, &swaps); // Передаємо адреси змінних

    end = clock();

    // Вимірювання часу у мікросекундах
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000000;
    printf("\nЧас сортування: %.2f мкс\n", time_taken);
    printf("Кількість порівнянь: %d\n", comparisons);
    printf("Кількість перестановок: %d\n", swaps);
    
    // Запис результатів у файл output.txt
    write_array_to_file("output.txt", arr, n);
    printf("Відсортований масив записано до файлу 'output.txt'\n");
    free(arr);
    return 0;
}
