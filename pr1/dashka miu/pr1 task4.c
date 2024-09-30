#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// ������� ��� ����������� ������� ����� �� ���������� �����
void SieveOfAtkin(int n) {
    if (n < 2) {
        printf("����� ����� ������\n");
        return;
    }
    bool sieve[n + 1];
    int i, x, y, j;
    // ���������� ����� false
    for (i = 0; i <= n; i++) {
        sieve[i] = false;
    }
    // �������� ���� ��� �������� � ������
    for (x = 1; x * x <= n; x++) {
        for (y = 1; y * y <= n; y++) {
            int num = (4 * x * x + y * y);
            if (num <= n && (num % 12 == 1 || num % 12 == 5)) {
                sieve[num] = !sieve[num];
            }

            num = (3 * x * x + y * y);
            if (num <= n && num % 12 == 7) {
                sieve[num] = !sieve[num];
            }

            num = (3 * x * x - y * y);
            if (x > y && num <= n && num % 12 == 11) {
                sieve[num] = !sieve[num];
            }
        }
    }

    // ��������� �� ����� �������� ������� �����
    for (i = 5; i * i <= n; i++) {
        if (sieve[i]) {
            for (j = i * i; j <= n; j += i * i) {
                sieve[j] = false;
            }
        }
    }

    // ��������� ������� �����
    printf("����� ����� �� %d: ", n);
    if (n > 2) {
        printf("2 ");
    }
    if (n > 3) {
        printf("3 ");
    }

    for (i = 5; i <= n; i++) {
        if (sieve[i]) {
            printf("%d ", i);
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
	
    SieveOfAtkin(n);

    return 0;
}
