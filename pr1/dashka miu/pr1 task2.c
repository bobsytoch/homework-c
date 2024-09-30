#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Функція для знаходження простих чисел за алгоритмом Ератосфена
void SieveOfEratosthene(int n) {
    bool primes[n + 1];
    // Ініціалізація масиву
    int i, j;
    for (i = 0; i <= n; i++) {
        primes[i] = true;
    }
    // Викидання кратних чисел
    for (j = 2; j <= sqrt(n); j++) {
        if (primes[j]) {
            for (i = j * j; i <= n; i += j) {
                primes[i] = false;
            }
        }
    }
    // Виведення простих чисел
    printf("Прості числа до %d: ", n);
    for (j = 2; j <= n; j++) {
        if (primes[j]) {
            printf("%d ", j);
        }
    }
    printf("\n");
}

int main() {

    system("chcp 1251");
    system("cls");

    int n;
    printf("Алгоритм Ератосфена (знаходження всіх простих чисел до заданого числа n)\n\n");
    printf("Введіть число n: ");
    scanf("%d", &n);
    printf("\n");

    SieveOfEratosthene(n);

    return 0;
}
