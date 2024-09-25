#include <stdio.h>

int main() {
    int n;
    printf("Введіть ціле число більше 2: ");
    scanf("%d", &n);

    int primes[n + 1];

    // позначаємо всі числа як парні
    for (int i = 0; i <= n; i++) primes[i] = 1;

    // помічаємо нулем всі числа, що кратні на прості 2, 3, 5 та 7 за допомогою цього алгоритма
    for (int p = 2; p * p <= n; p++)
        // перевірка в раз того, що програма вже прошла через даний сет чисел кратних на два
        if (primes[p] == 1)
            for (int i = p * p; i <= n; i += p) primes[i] = 0;

    printf("Прості числа до %d:\n", n);
    // виводимо всі числа, помічені як прості
    for (int p = 2; p <= n; p++) if (primes[p]) printf("%d ", p);

    printf("\n");
    return 0;
}