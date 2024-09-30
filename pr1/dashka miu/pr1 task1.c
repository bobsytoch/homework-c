#include <stdio.h>

// Функція для обчислення GCD за алгоритмом Евкліда
int findGCD(int a, int b) {
    if (b == 0) {
        return a;
    }
    else {
        return findGCD(b, a % b);
    }
}

int main() {
	
	system("chcp 1251");
	system("cls");
	
    int num1, num2;
    
    printf("Введіть перше число: ");
    scanf("%d", &num1);
    
    printf("Введіть друге число: ");
    scanf("%d", &num2);

    printf("\nНайбільший спільний дільник: %d\n", findGCD(num1, num2));

    return 0;
}
