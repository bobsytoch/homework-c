#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void insert(Node **table, int hash, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = table[hash];
    table[hash] = newNode;
}

int countCollisions(Node **table, int tableSize) {
    int collisions = 0;
    for (int i = 0; i < tableSize; i++) {
        int count = 0;
        Node *current = table[i];
        while (current) {
            count++;
            current = current->next;
        }
        if (count > 1) 
            collisions += count - 1;
    }
    return collisions;
}

void freeTable(Node **table, int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        Node *current = table[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

void fillArrayRand(int *array, int size, int max) {
    int used[max + 1];
    for (int i = 0; i <= max; i++) 
        used[i] = 0;

    int count = 0;
    while (count < size) {
        int num = rand() % max + 1;
        if (!used[num]) {
            used[num] = 1;
            array[count++] = num;
        }
    }
}

void printHashTable(Node **table, int tableSize) {
    printf("\nTable:\n");
    for (int i = 0; i < tableSize; i++) {
        if (table[i] != NULL) {
            printf("Key %d: ", i);
            Node *current = table[i];
            while (current) {
                printf("%d -> ", current->value);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

int main() {
    srand(time(0));

    int numbers[100];
    fillArrayRand(numbers, 100, 99999);
    int tableSizes[] = {10, 100};
    for (int i = 0; i < 2; i++) {
        int tableSize = tableSizes[i];
        Node *hashTable[tableSize];
        for (int j = 0; j < tableSize; j++) 
            hashTable[j] = 0;

        for (int j = 0; j < 100; j++) 
            insert(hashTable, numbers[j] % tableSize, numbers[j]);

        printHashTable(hashTable, tableSize);
        printf("Collisions for table size %d: %d\n", tableSize, countCollisions(hashTable, tableSize));
        freeTable(hashTable, tableSize);
    }

    return 0;
}
