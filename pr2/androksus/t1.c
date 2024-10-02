#include <stdio.h>
#include <time.h>

int count_combinations(int amount, int coins[], int n) {
    if (amount == 0) {
        return 1;
    }
    if (amount < 0 || n <= 0) {
        return 0;
    }
    return count_combinations(amount - coins[n - 1], coins, n) + count_combinations(amount, coins, n - 1);
}

int main() {
    int coins[] = {1, 5, 10, 25, 50};
    int amount;

    printf("Введіть суму в центах: ");
    scanf("%d", &amount);

    // Вимірювання часу
    clock_t start_time = clock();

    int result = count_combinations(amount, coins, 5);

    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Кількість комбінацій для розміну суми %d центів: %d\n", amount, result);
    printf("Час виконання: %.2f секунд\n", time_taken);

    return 0;
}
