#include <stdio.h>
#include <math.h>

void shellGaps(int gaps[], int gapCount, int arraySize) {
    int i = 0;
    for (int g = arraySize / 2; g >= 1 && i < gapCount; i++, g /= 2) 
    {
        gaps[i] = g;
    }

    if (i < gapCount - 1) for (i; i < gapCount; i++) gaps[i] = 0;
}

int ciura[] = { 1, 4, 10, 23, 57, 132, 301, 701 };
void ciuraGaps(int gaps[], int gapCount, int arraySize) {
    for (int i = 0; i  < gapCount; i++) 
        gaps[gapCount-i-1] = i < 8 ? ciura[i] : 0;
}

void frankGaps(int gaps[], int gapCount, int arraySize) {
    for (int i = 1, g = 2 * (arraySize / 4) + 1; i <= gapCount; i++, g = 2 * (arraySize / (int) pow(2, i+1)) + 1) 
    {
        gaps[i-1] = g;
    }
}

void papernovGaps(int gaps[], int gapCount) {
    gaps[gapCount - 1] = 1;
    for (int i = 1; i < gapCount; i++) 
        gaps[gapCount-i-1] = pow(2, i) + 1;
}

void prattGaps(int gaps[], int gapCount, int arraySize) {
    int i2 = 0, i3 = 0;
    int next2 = 2, next3 = 3;
    int current = 1;

    int temp[gapCount];
    int index = 0;

    temp[index++] = current;
    while (index < gapCount) {
        current = (next2 < next3) ? next2 : next3;
        temp[index++] = current;

        if (current == next2) 
            next2 = temp[++i2] * 2;
        if (current == next3) 
            next3 = temp[++i3] * 3;
    }

    for (int i = 0; i < gapCount; i++) 
        gaps[i] = temp[gapCount - 1 - i];
}

void knuthGaps(int gaps[], int gapCount, int arraySize) {
    int c = ceil((double)arraySize/3);
    int i = 0;
    for (int g = (pow(3, i+1))/2; g <= c && i < gapCount; i++, g = (pow(3, i+1))/2) 
        gaps[gapCount - i - 1] = g;

    if (i < gapCount - 1) for (i; i < gapCount; i++) gaps[gapCount - i - 1] = 0;
}

int coprimes[] = { 1, 3, 7, 16, 41, 101, 247, 613, 1529, 3821, 9539, 23843, 59611, 149015, 372539, 931327, 2328307, 5820767, 14551919, 36379789, 90949471, 227373677, 568434193, 1421085473 };
void incerpiGaps(int gaps[], int gapCount) {
    for (int k = 0; k < gapCount; k++) { 
        int r = sqrt(2*k + sqrt(2*k));
        int b = 0.5*(r*r + r) - k;
        int mult = 1;

        for (int q = 0; q <= r; q++) {
            if (q == b) continue;
            mult *= coprimes[q];
        }

        gaps[gapCount-k-1] = mult;
    }
}

void sedgewick82Gaps(int gaps[], int gapCount) {
    gaps[gapCount - 1] = 1;
    for (int i = 1; i < gapCount; i++) 
    {
        gaps[gapCount-i-1] = pow(4, i) + 3 * pow(2, i-1) + 1;
    }
}

void sedgewick86Gaps(int gaps[], int gapCount) {
    gaps[gapCount - 1] = 1;
    for (int i = 1; i < gapCount; i++) 
    {
        gaps[gapCount-i-1] = i % 2 ?
            8*pow(2, i) - 6*pow(2, (i+1)/2) + 1 :
            9*(pow(2, i) - pow(2, i/2)) + 1;
    }
}

void tokudaGaps(int gaps[], int gapCount) {
    for (int i = 0; i < gapCount; i++)
        gaps[gapCount-i-1] = ceil((pow(9.0/4, i+1) - 1) / (9.0/4 - 1));
}

void printArray(int arr[], int size) {
    printf("[ ");
    for (int i = 0; i < size-1; i++) 
        printf("%d, ", arr[i]);
    printf("%d ]\n", arr[size-1]);
}

int main() {
    int N;
    printf("Enter array length: ");
    scanf("%d", &N);
    if (N < 1) {
        printf("Arrays can't have negative length.");
        return 1;
    }

    int gapCount;
    printf("Enter gap amount: ");
    scanf("%d", &gapCount);
    if (gapCount < 1) {
        printf("Arrays can't have negative length.");
        return 1;
    }

    int gapsType;
    printf("Shellsort gaps:\n");
    printf("1 - Shell\n");
    printf("2 - Frank & Lazarus\n");
    printf("3 - Papernov & Stasevich\n");
    printf("4 - Pratt\n");
    printf("5 - Knuth\n");
    printf("6 - Incerpi & Sedgewick\n");
    printf("7 - Sedgewick, 1982\n");
    printf("8 - Sedgewick, 1986\n");
    printf("9 - Tokuda\n");
    printf("10 - Ciura\n");
    printf("0 - EXIT\n");
    
    int gaps[gapCount];

    while (1) {
        printf("Choose your gap type: ");
        scanf("%d", &gapsType);

        switch (gapsType) {
            case 0: return 0;
            case 1: shellGaps(gaps, gapCount, N); break;
            case 2: frankGaps(gaps, gapCount, N); break;
            case 3: papernovGaps(gaps, gapCount); break;
            case 4: prattGaps(gaps, gapCount, N); break;
            case 5: knuthGaps(gaps, gapCount, N); break;
            case 6: incerpiGaps(gaps, gapCount); break;
            case 7: sedgewick82Gaps(gaps, gapCount); break;
            case 8: sedgewick86Gaps(gaps, gapCount); break;
            case 9: tokudaGaps(gaps, gapCount); break;
            case 10: ciuraGaps(gaps, gapCount, N); break;
            default: printf("Gap type is incorrect. Try again.\n");
        }

        printf("Gaps: ");
        printArray(gaps, gapCount);
    }

    return 0;
}