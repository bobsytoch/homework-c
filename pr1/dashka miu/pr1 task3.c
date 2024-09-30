#include <stdio.h>
#include <stdbool.h>

// ������� ��� ����������� ������� ����� �� ���������� ���������
void SieveOfSundaram(int n) {
    int nNew = (n - 1) / 2;
    bool marked[nNew + 1];

    // ����������� ������
    int i, j;
    for (i = 0; i <= nNew; i++) {
        marked[i] = false;
    }

    // ������������� ����� �� �������� i + j + 2 * i * j
    for (i = 1; i <= nNew; i++) {
        for (j = i; (i + j + 2 * i * j) <= nNew; j++) {
            marked[i + j + 2 * i * j] = true;
        }
    }

    // ��������� ������� �����
    printf("����� ����� �� %d: ", n);
    if (n > 2) {
        printf("2 ");
    }

    for (i = 1; i <= nNew; i++) {
        if (!marked[i]) {
            printf("%d ", 2 * i + 1);
        }
    }
    printf("\n");
}

int main() {
	
	system("chcp 1251");
	system("cls");
	
    int n;
    printf("������ ����� n ��� ����������� ������� ����� �� n: ");
    scanf("%d", &n);
    printf("\n");

    if (n < 2) {
        printf("����� ������� ���� ����� �� 1.\n");
    } else {
        SieveOfSundaram(n);
    }

    return 0;
}
