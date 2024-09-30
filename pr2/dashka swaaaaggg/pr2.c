#include <stdio.h>
#include <time.h>

int main() {
    system("chcp 1251");
    system("cls");

    int sum;

    printf("������ ���� (� ������): ");
    scanf("%d", &sum);

    // ������� �����
    int coins[] = {1, 5, 10, 25, 50};
    int count = 0;

    // ������� ���������� ����
    clock_t start = clock();

    // ����� ����� ����: ���������� �� ������ ��������� �����
    int i, j, k, l, m;
    
    for (i = 0; i <= sum / coins[4]; i++) {
        for (j = 0; j <= sum / coins[3]; j++) {
            for (k = 0; k <= sum / coins[2]; k++) {
                for (l = 0; l <= sum / coins[1]; l++) {
                    for (m = 0; m <= sum / coins[0]; m++) {
                        if (i * coins[4] + j * coins[3] + k * coins[2] + l * coins[1] + m * coins[0] == sum) {
                            count++;
                        }
                    }
                }
            }
        }
    }

    // ʳ���� ���������� ����
    clock_t end = clock();

    // ���������� ���� ���������
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nʳ������ �������� ���������: %d\n", count);
    printf("���, ���������� �� ����������: %.6f ������\n", time_spent);

    return 0;
}

