#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Функція для знаходження простих чисел за алгоритмом Аткіна
void SieveOfAtkin(int n) {
    if (n < 2) {
        printf("Прості числа відсутні\n");
        return;
    }
    bool sieve[n + 1];
    int i, x, y, j;
    // Ініціалізуємо масив false
    for (i = 0; i <= n; i++) {
        sieve[i] = false;
    }
    // Перевірка умов для квадратів і модулів
    for (x = 1; x * x <= n; x++) {
        for (y = 1; y * y <= n; y++) {
            int num = (4 * x * x + y * y);
            if (num <= n && (num % 12 == 1 || num % 12 == 5)) {
                sieve[num] = !sieve[num];
            }

            num = (3 * x * x + y * y);
            if (num <= n && num % 12 == 7) {
                sieve[num] = !sieve[num];
            }

            num = (3 * x * x - y * y);
            if (x > y && num <= n && num % 12 == 11) {
                sieve[num] = !sieve[num];
            }
        }
    }

    // Позначаємо всі кратні квадратів простих чисел
    for (i = 5; i * i <= n; i++) {
        if (sieve[i]) {
            for (j = i * i; j <= n; j += i * i) {
                sieve[j] = false;
            }
        }
    }

    // Виведення простих чисел
    printf("Прості числа до %d: ", n);
    if (n > 2) {
        printf("2 ");
    }
    if (n > 3) {
        printf("3 ");
    }

    for (i = 5; i <= n; i++) {
        if (sieve[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    system("chcp 1251");
    system("cls");

    int n;
    printf("Введіть число n для знаходження простих чисел до n: ");
    scanf("%d", &n);
	printf("\n");
	
    SieveOfAtkin(n);

    return 0;
}
