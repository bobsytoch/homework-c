#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Функція для реалізації сітки Ератосфена
void Eratosthenes(int n) {
    bool isPrime[n+1];
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true;
    }
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i <= sqrt(n); i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    printf("Прості числа до %d: ", n);
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Введіть число n: ");
    scanf("%d", &n);
    
    Eratosthenes(n);
    
    return 0;
}
