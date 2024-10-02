#include <stdio.h>

int main() {
 	int M, N;
    	printf("Вкажіть число M: ");
    	scanf("%d", &M);
    	printf("Вкажіть число N: ");
    	scanf("%d", &N);
    
    while (M != N) {
        if (M > N) M -= N;
        else N -= M;
    }

    printf("НСД: %d\n", M);
    return 0;
}