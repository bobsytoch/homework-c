#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 10

// Функція для пошуку з поверненням
void FindAPath(int arr[], int position, char *path, int *found, int visited[]) {
    // Якщо досягли кінцевої позиції
    if (position == SIZE - 1) {
        printf("%s0\n", path); // Додаємо 0 до шляху
        *found = 1; // Відзначаємо, що знайдено хоча б одне рішення
        return;
    }

    int step = arr[position];

    // Рух вправо
    if (position + step < SIZE && !visited[position + step]) {
        visited[position + step] = 1; // Помічаємо позицію як відвідану
        char newPath[100];
        snprintf(newPath, sizeof(newPath), "%s%d R ", path, step);
        FindAPath(arr, position + step, newPath, found, visited);
        visited[position + step] = 0; // Відмічаємо позицію як не відвідану
    }

    // Рух вліво
    if (position - step >= 0 && !visited[position - step]) {
        visited[position - step] = 1; // Помічаємо позицію як відвідану
        char newPath[100];
        snprintf(newPath, sizeof(newPath), "%s%d L ", path, step);
        FindAPath(arr, position - step, newPath, found, visited);
        visited[position - step] = 0; // Відмічаємо позицію як не відвідану
    }
}

int main() {
    srand(time(NULL));
    int arr[SIZE];

    // Генерація масиву випадкових чисел (не більше 9)
    for (int i = 0; i < SIZE - 1; i++) {
        arr[i] = rand() % 9 + 1;
    }
    arr[SIZE - 1] = 0; // Останній елемент завжди 0

    // Виведення масиву
    printf("Масив: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\nВаріанти рішень:\n");

    // Пошук всіх можливих рішень
    char path[100] = ""; // Ініціалізація пустого шляху
    int found = 0; // Прапор для перевірки, чи знайдено рішення
    int visited[SIZE] = {0}; // Масив для відстеження відвіданих позицій
    visited[0] = 1; // Починаємо з першої позиції

    FindAPath(arr, 0, path, &found, visited);

    // Якщо не знайдено жодного рішення
    if (!found) {
        printf("Рішення не знайдено.\n");
    }

    return 0;
}
