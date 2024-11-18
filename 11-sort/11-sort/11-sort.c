#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// ���� ������ ���� �Լ�
void generateRandomData(int data[]) {
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000;  // 0~999 ������ �� ����
    }
}

// ���� ���� �Լ� (���� ���� ��� ����)
void doSelectionSort(int data[]) {
    int temp[SIZE];
    for (int i = 0; i < SIZE; i++) temp[i] = data[i];  // data �迭 ����

    printf("Selection Sort:\n");
    for (int i = 0; i < SIZE - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < SIZE; j++) {
            if (temp[j] < temp[minIdx]) {
                minIdx = j;
            }
        }
        int tmp = temp[i];
        temp[i] = temp[minIdx];
        temp[minIdx] = tmp;

        // ���� ������ 10������ ��� (10, 20, ..., ������ �ܰ�)
        if ((i + 1) % 10 == 0 || i == SIZE - 2) {
            printf("Step %d: ", i + 1);
            for (int k = 0; k < SIZE; k++) {
                printf("%d ", temp[k]);
            }
            printf("\n");
        }
    }
}

// ���� ���� �Լ� (20ȸ ���� �� ��� �� Ƚ�� ���)
void doInsertionSort(int data[]) {
    int totalCompareCount = 0;

    for (int t = 0; t < 20; t++) {  // 20ȸ ����
        generateRandomData(data);  // ��ȸ �ٸ� ���� �����͸� ����
        int temp[SIZE];
        int compareCount = 0;
        for (int i = 0; i < SIZE; i++) temp[i] = data[i];  // data �迭 ����

        for (int i = 1; i < SIZE; i++) {
            int key = temp[i];
            int j = i - 1;
            while (j >= 0 && temp[j] > key) {
                temp[j + 1] = temp[j];
                j--;
                compareCount++;
            }
            temp[j + 1] = key;
            compareCount++;
        }
        totalCompareCount += compareCount;
    }

    printf("\nInsertion Sort Compare Average: %d\n", totalCompareCount / 20);

    // ������ ���� ��� ���
    printf("Insertion Sort Result: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

// ���� ���� �Լ� (20ȸ ���� �� ��� �̵� Ƚ�� ���)
void doBubbleSort(int data[]) {
    int totalMoveCount = 0;

    for (int t = 0; t < 20; t++) {  // 20ȸ ����
        generateRandomData(data);  // ��ȸ �ٸ� ���� �����͸� ����
        int temp[SIZE];
        int moveCount = 0;
        for (int i = 0; i < SIZE; i++) temp[i] = data[i];  // data �迭 ����

        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (temp[j] > temp[j + 1]) {
                    int tmp = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = tmp;
                    moveCount += 3;  // �� swap���� 3�� �̵�
                }
            }
        }
        totalMoveCount += moveCount;
    }

    printf("\nBubble Sort Move Average: %d\n", totalMoveCount / 20);

    // ������ ���� ��� ���
    printf("Bubble Sort Result: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

// main �Լ�
int main() {
    int randomData[SIZE];
    srand(time(NULL));  // �Ź� �ٸ� ���� ���� �����ϱ� ���� �õ� ����

    generateRandomData(randomData);  // �ʱ� ���� ������ ����
    doSelectionSort(randomData);  // ���� ���� ���� �� ���� ���

    doInsertionSort(randomData);  // ���� ���� 20ȸ ����, ��� �� Ƚ�� ���

    doBubbleSort(randomData);     // ���� ���� 20ȸ ����, ��� �̵� Ƚ�� ���

    return 0;
}
