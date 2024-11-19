#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printBinary(int num) {
    for (int i = 7; i >= 0; i--) 
        printf("%d", (num >> i) & 1);
}

int grayCode(int num) { return num ^ (num >> 1); }

int main() {
    srand(time(0));

    int arr[10];
    int grayArr[10];

    printf("%4s | %8s | %5s | %8s\n",
        "num", "binary", "gray", "gray binary");

    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
        grayArr[i] = grayCode(arr[i]);

        printf("%4d | ", arr[i]);
        printBinary(arr[i]);
        printf(" | %5d | ", grayArr[i]);
        printBinary(grayArr[i]);
        printf("\n");
    }

    return 0;
}
