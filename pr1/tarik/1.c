#include <stdio.h>

int main() {
    unsigned int M, N;
    printf("Введіть число M: ");
    scanf("%d", &M);
    printf("Введіть число N: ");
    scanf("%d", &N);
    
    while (M != N) {
        if (M > N) M -= N;
        else N -= M;
    }

    printf("Дільник: %d\n", M);
    return 0;
}