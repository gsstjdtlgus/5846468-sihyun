#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

void generateRandomNumbers(int* array) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 ������ ���� ����
    }
}

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("...\n");
}

void doShellSort(int* originalArray, int divisor, int* comparisonCount, int* moveCount) {
    int array[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = originalArray[i]; // ���� �迭 ����
    }

    *comparisonCount = 0;
    *moveCount = 0;
    int gap = ARRAY_SIZE / divisor;

    while (gap > 0) {
        printf("Sorting with gap = %d:\n", gap);
        for (int i = gap; i < ARRAY_SIZE; i++) {
            int temp = array[i];
            (*moveCount)++; // temp�� ����

            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
                (*comparisonCount)++;
                (*moveCount)++; // array[j]�� �� ����
            }

            array[j] = temp;
            (*moveCount)++; // temp���� �� ����
        }
        printArray(array, 20); // ù 20�� ���
        gap /= divisor;
    }

    printf("Sorted shellArray (gap = %d):\n", divisor);
    printArray(array, 20);
}

int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    srand(time(NULL));
    generateRandomNumbers(array);

    // Shell Sort
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    return 0;
}
