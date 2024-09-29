#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

// Структура для збереження кроку (значення і напрямок)
typedef struct {
    int value;
    char direction;
} Step;

// Функція для пошуку всіх шляхів
void solvePuzzle(int *arr, int size, int pos, Step *steps, int stepIndex, int *found) {
    // Перевірка виходу за межі масиву або зациклення
    if (pos < 0 || pos >= size || stepIndex >= size) {
        return;
    }
    
    if (arr[pos] == 0 && pos == size - 1) {
        // Дісталися до останньої клітинки
        for (int i = 0; i < stepIndex; i++) {
            printf("%d %c ", steps[i].value, steps[i].direction);
        }
        printf("0\n"); // Остання клітинка завжди 0
        *found = 1; // Встановлюємо, що рішення знайдено
        return;
    }

    // Якщо рішення вже знайдено, виходимо
    if (*found) return;

    // Додаємо поточний крок (вправо і вліво)
    if (pos + arr[pos] < size && !*found) {
        steps[stepIndex].value = arr[pos];
        steps[stepIndex].direction = 'R';
        solvePuzzle(arr, size, pos + arr[pos], steps, stepIndex + 1, found);
    }
    if (pos - arr[pos] >= 0 && !*found) {
        steps[stepIndex].value = arr[pos];
        steps[stepIndex].direction = 'L';
        solvePuzzle(arr, size, pos - arr[pos], steps, stepIndex + 1, found);
    }
}

int main() {
    srand(time(0)); // Ініціалізація генератора випадкових чисел
    
    int arr[SIZE];
    Step steps[SIZE]; // Масив для збереження кроків
    int found = 0; // Прапорець для позначення знайденого рішення
    
    // Заповнюємо масив випадковими значеннями (від 1 до 9), крім останнього елемента
    for (int i = 0; i < SIZE - 1; i++) {
        arr[i] = rand() % 9 + 1; // Числа від 1 до 9
    }
    arr[SIZE - 1] = 0; // Останній елемент масиву — завжди 0
    
    // Виводимо вихідний масив
    printf("Вихідний масив: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Шукаємо всі варіанти рішень
    solvePuzzle(arr, SIZE, 0, steps, 0, &found);
    
    if (!found) {
        printf("Рішення не знайдено.\n");
    }

    return 0;
}
