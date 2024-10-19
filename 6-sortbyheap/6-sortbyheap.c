#include <stdio.h>
#include <stdlib.h>

// �� ������ �����͸� ���� ��ȯ�ϴ� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �迭�� ��Ҹ� ����ϴ� �Լ�
void printArray(int inputData[], int n) {
    for (int j = 0; j < n; j++) {
        printf("%d ", inputData[j]);
    }
    printf("\n");
}

// �ε��� i�� ��Ʈ�� �ϴ� ����Ʈ���� �� �Ӽ��� �����ϴ� �Լ�
void resortHeap(int inputData[], int n, int i) {
    int largest = i; // ��Ʈ�� largest�� �ʱ�ȭ
    int left = 2 * i + 1; // ���� �ڽ��� �ε���
    int right = 2 * i + 2; // ������ �ڽ��� �ε���

    // ���� �ڽ��� ��Ʈ���� ũ��
    if (left < n && inputData[left] > inputData[largest]) {
        largest = left;
    }

    // ������ �ڽ��� ���ݱ����� largest���� ũ��
    if (right < n && inputData[right] > inputData[largest]) {
        largest = right;
    }

    // largest�� ��Ʈ�� �ƴ϶��, ��ȯ�ϰ� ��� ��ȭ
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

// �迭�κ��� �ִ� ���� �����ϴ� �Լ�
void BuildMaxHeap(int inputData[], int n) {
    int startIdx = n / 2 - 1; // ������ ���� ��忡�� ����
    for (int i = startIdx; i >= 0; i--) {
        resortHeap(inputData, n, i);
    }
}

// �Է� �迭�� ���� �� ������ �����ϴ� �Լ�
void BuildMaxHeapAndSort(int inputData[], int n) {
    // �ִ� ���� �����ϰ� �߰� ���¸� ���
    for (int i = 0; i < n; i++) {
        BuildMaxHeap(inputData, i + 1);
        printArray(inputData, i + 1);  // ���� �迭 ���� ���
    }

    // ������ ��Ҹ� �ϳ��� �����Ͽ� �迭�� ����
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]); // ���� ��Ʈ�� ������ �̵�
        resortHeap(inputData, i, 0); // ��ҵ� ���� ���� �ִ� ��ȭ ȣ��

        // ���ĵ� �κ��� ���� ���� ���
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

// �� ������ �����ϴ� ���� �Լ�
int main(void) {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]); // �迭�� ũ�� ���

    printf("<Sort>\n"); // ���� ���� ���� �˸�
    BuildMaxHeapAndSort(inputData, size); // �� ���� ����

    printf("\nSorted Array:\n"); // ���� ���ĵ� �迭 ���
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0; // �������� �ϷḦ ��Ÿ��
}

