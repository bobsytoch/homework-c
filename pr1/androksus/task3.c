#include <stdio.h>
#include <stdbool.h>

void Sundaram(int n) {
    int limit = (n - 1) / 2;
    bool marked[limit + 1];

    // Ініціалізуємо всі числа як прості
    for (int i = 0; i <= limit; i++) {
        marked[i] = false;
    }

    // Викреслюємо числа за допомогою формули i + j + 2 * i * j
    for (int i = 1; i <= limit; i++) {
        for (int j = i; (i + j + 2 * i * j) <= limit; j++) {
            marked[i + j + 2 * i * j] = true;
        }
    }

    // Виводимо прості числа
    printf("Прості числа до %d: 2 ", n);
    for (int i = 1; i <= limit; i++) {
        if (!marked[i]) {
            printf("%d ", 2 * i + 1);
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Введіть число n: ");
    scanf("%d", &n);
    Sundaram(n);
    return 0;
}
