#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A 0.618033

// Функція для генерації унікальних випадкових чисел
void generateUniqueArray(int *arr, int n, int max_val) {
    int i = 0;
    while (i < n) {
        int num = rand() % max_val;
        int is_unique = 1;
        for (int j = 0; j < i; j++) 
            if (arr[j] == num) {
                is_unique = 0;
                break;
            }
        if (is_unique) arr[i++] = num;
    }
}

int hashMultiply(int key, int m) {
    return (int)(m * (key * A - (int)(key * A)));
}

int countCollisions(int *arr, int n, int m) {
    int collisions = 0;
    int hashTable[m];
    for (int i = 0; i < m; i++) hashTable[i] = -1;
    for (int i = 0; i < n; i++) {
        int hash = hashMultiply(arr[i], m);
        if (hashTable[hash] != -1)  collisions++;
        hashTable[hash] = arr[i];
    }
    return collisions;
}

void createHashTable(int *arr, int n, int m) {
    char *hashTable[m];
    for (int i = 0; i < m; i++) 
        hashTable[i] = NULL;

    for (int i = 0; i < n; i++) {
        int hash = hashMultiply(arr[i], m);
        int attempts = 0;

        while (hashTable[hash] != NULL && attempts < m) {
            hash = (hash + 1) % m;
            attempts++;
        }

        if (attempts == m) {
            printf("Хеш-таблиця переповнена, неможливо вставити %d\n", arr[i]);
            continue;
        }

        char *value = (char *)malloc(12 * sizeof(char));
        sprintf(value, "%d", arr[i]);
        hashTable[hash] = value;
    }

    for (int i = 0; i < m; i++) 
        if (hashTable[i] != NULL) 
            printf("key: %d, value: %s\n", i, hashTable[i]);

    for (int i = 0; i < m; i++) 
        if (hashTable[i] != NULL) 
            free(hashTable[i]);
}


int main() {
    srand(time(0));

    int numbers[100];
    generateUniqueArray(numbers, 100, 100000);
    printf("Collisions for table size 10: %d\n", countCollisions(numbers, 100, 10));
    printf("Collisions for table size 100: %d\n", countCollisions(numbers, 100, 100));

    createHashTable(numbers, 100, 10);
    createHashTable(numbers, 100, 100);

    return 0;
}
