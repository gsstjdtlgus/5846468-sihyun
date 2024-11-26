#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0; // �� Ƚ��
int moveCount = 0;       // �̵� Ƚ��
int totalComparisons = 0;
int totalMoves = 0;
int isFirst = 0;
int rounds = 0;

// ���� �迭 ���� �Լ�
void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999�� ���� ��
    }
}

// �迭 ��� �Լ�
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
}

// �պ� �Լ�
void merge(int array[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = array[left + i];
        moveCount++;
    }
    for (int i = 0; i < n2; i++) {
        R[i] = array[mid + 1 + i];
        moveCount++;
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        comparisonCount++;
        if (L[i] <= R[j]) {
            array[k++] = L[i++];
        }
        else {
            array[k++] = R[j++];
        }
        moveCount++;
    }

    while (i < n1) {
        array[k++] = L[i++];
        moveCount++;
    }

    while (j < n2) {
        array[k++] = R[j++];
        moveCount++;
    }

    free(L);
    free(R);
}

// �պ� ���� �Լ�
void doMergeSort(int array[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        doMergeSort(array, left, mid);
        doMergeSort(array, mid + 1, right);
        merge(array, left, mid, right);

        // �߰� ���� ���
        rounds++;
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 0; i < 10; i++) { // 0~9 ��
                printf("%3d ", array[i]);
            }
            printf("| ");
            for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) { // �߾�-1 ~ �߾�+10
                printf("%3d ", array[i]);
            }
            printf("\n\n");
        }
    }
}

// ���� �Լ�
int main() {
    int array[SIZE];
    srand((unsigned int)time(NULL)); // ���� �õ� ����

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE - 1);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            doMergeSort(array, 0, SIZE - 1);
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\n\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
