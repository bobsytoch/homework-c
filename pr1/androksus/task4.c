#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void Atkin(int n) {
    if (n < 2) {
        printf("Простих чисел немає.\n");
        return;
    }
	printf("Всі прості числа до %d: ", n);
	if (n >= 2) printf(" 2 ");
    if (n >= 3) printf(" 3 ");
                            
    bool sieve[n + 1];
    for (int i = 0; i <= n; i++) {
        sieve[i] = false;
    }

    // Основні формули для знаходження простих чисел
    for (int x = 1; x * x <= n; x++) {
        for (int y = 1; y * y <= n; y++) {
            int num = 4 * x * x + y * y;
            if (num <= n && (num % 12 == 1 || num % 12 == 5)) {
                sieve[num] ^= true;
            }

            num = 3 * x * x + y * y;
            if (num <= n && num % 12 == 7) {
                sieve[num] ^= true;
            }

            num = 3 * x * x - y * y;
            if (x > y && num <= n && num % 12 == 11) {
                sieve[num] ^= true;
            }
        }
    }

    // Викреслюємо всі кратні квадратів
    for (int i = 5; i * i <= n; i++) {
        if (sieve[i]) {
            for (int j = i * i; j <= n; j += i * i) {
                sieve[j] = false;
            }
        }
    }

    // Виводимо всі прості числа
    for (int i = 5; i <= n; i++) {
        if (sieve[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Введіть число n: ");
    scanf("%d", &n);
    Atkin(n);
    return 0;
}
