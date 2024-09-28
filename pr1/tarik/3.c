#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функція для реалізації решета Аткіна
void atkinSieve(int n) {
    // Створюємо масив для позначення можливих простих чисел
    int *sieve = (int*)calloc(n + 1, sizeof(int));

    for (int x = 1; x * x <= n; x++) {
        for (int y = 1; y * y <= n; y++) {
            int num = 4 * x * x + y * y;
            if (num <= n && (num % 12 == 1 || num % 12 == 5)) {
                sieve[num] ^= 1;
            }

            num = 3 * x * x + y * y;
            if (num <= n && num % 12 == 7) {
                sieve[num] ^= 1;
            }

            num = 3 * x * x - y * y;
            if (x > y && num <= n && num % 12 == 11) {
                sieve[num] ^= 1;
            }
        }
    }

    // Позначаємо всі кратні квадратів як непотрібні
    for (int r = 5; r * r <= n; r++) {
        if (sieve[r]) {
            for (int i = r * r; i <= n; i += r * r) {
                sieve[i] = 0;
            }
        }
    }

    // Виводимо числа 2 і 3
    printf("2 ");
    if (n >= 3) printf("3 ");

    // Виводимо інші прості числа
    for (int i = 5; i <= n; i++) 
        if (sieve[i]) 
            printf("%d ", i);
    
    printf("\n");

    // Звільнення пам'яті
    free(sieve);
}

int main() {
    int n;
    printf("Введіть межу для пошуку простих чисел: ");
    scanf("%d", &n);
    if (n < 2) return printf("Межа має бути більше двох");

    printf("Прості числа менші за %d:\n", n);
    atkinSieve(n);

    return 0;
}
