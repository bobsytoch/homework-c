#include <stdio.h>

// ������� ��� ���������� GCD �� ���������� ������
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
    
    printf("������ ����� �����: ");
    scanf("%d", &num1);
    
    printf("������ ����� �����: ");
    scanf("%d", &num2);

    printf("\n��������� ������� ������: %d\n", findGCD(num1, num2));

    return 0;
}
