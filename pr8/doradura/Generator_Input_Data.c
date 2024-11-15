#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_sorted_array(const char *filename, int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Помилка при створенні файлу.");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", i + 1);
    }
    fclose(file);
}

void generate_reverse_sorted_array(const char *filename, int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Помилка при створенні файлу.");
        return;
    }

    for (int i = n; i > 0; i--) {
        fprintf(file, "%d ", i);
    }
    fclose(file);
}

void generate_random_array(const char *filename, int n) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Помилка при створенні файлу.");
        return;
    }

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", rand() % n);
    }
    fclose(file);
}

int main() {
    int n;
    printf("Введіть кількість елементів у масиві: ");
    scanf("%d", &n);

    generate_sorted_array("sorted_input.txt", n);
    generate_reverse_sorted_array("reverse_sorted_input.txt", n);
    generate_random_array("random_input.txt", n);

    printf("Файли згенеровані: sorted_input.txt, reverse_sorted_input.txt, random_input.txt\n");

    return 0;
}
