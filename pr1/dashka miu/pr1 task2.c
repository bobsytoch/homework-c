#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// ������� ��� ����������� ������� ����� �� ���������� ����������
void SieveOfEratosthene(int n) {
    bool primes[n + 1];
    // ����������� ������
    int i, j;
    for (i = 0; i <= n; i++) {
        primes[i] = true;
    }
    // ��������� ������� �����
    for (j = 2; j <= sqrt(n); j++) {
        if (primes[j]) {
            for (i = j * j; i <= n; i += j) {
                primes[i] = false;
            }
        }
    }
    // ��������� ������� �����
    printf("����� ����� �� %d: ", n);
    for (j = 2; j <= n; j++) {
        if (primes[j]) {
            printf("%d ", j);
        }
    }
    printf("\n");
}

int main() {

    system("chcp 1251");
    system("cls");

    int n;
    printf("�������� ���������� (����������� ��� ������� ����� �� �������� ����� n)\n\n");
    printf("������ ����� n: ");
    scanf("%d", &n);
    printf("\n");

    SieveOfEratosthene(n);

    return 0;
}
