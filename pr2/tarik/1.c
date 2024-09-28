#include <stdio.h>
#include <time.h>

unsigned long long int count_combinations(int amount) {
    unsigned long long int comb = 0;
    for (int h = 0; h <= amount / 50; h++) 
        for (int q = 0; q <= (amount - h * 50) / 25; q++) 
            for (int t = 0; t <= (amount - h * 50 - q * 25) / 10; t++) 
                for (int f = 0; f <= (amount - h * 50 - q * 25 - t * 10) / 5; f++) 
                        comb++;

    return comb;
}

int main() {
    int amount;
    printf("Enter amount in cents: ");
    scanf("%d", &amount);
    if (amount < 1) return printf("Amount must be greater than 0\n");

    clock_t start = clock();
    unsigned long long int combinations = count_combinations(amount);
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Combination amount: %llu\n", combinations);
    printf("Clock: %.2fs\n", time_spent);

    return 0;
}