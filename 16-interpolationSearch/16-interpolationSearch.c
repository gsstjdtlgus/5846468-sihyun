#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000 // �迭 ũ�� ����

// 0���� 9999 ������ ������ ���ڷ� �迭 �ʱ�ȭ
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000; // ���� �� ����
    }
}

// QuickSort �˰��� ����
void QuickSort(int* array, int left, int right) {
    if (left >= right) return; // ���� ���� ����

    int pivot = array[(left + right) / 2]; // �ǹ� �� ����
    int i = left, j = right;

    // �ǹ��� �������� �迭 ����
    while (i <= j) {
        while (array[i] < pivot) i++;
        while (array[j] > pivot) j--;
        if (i <= j) {
            // �� ���� ��ȯ
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }

    // ��������� ���� ���� ����
    QuickSort(array, left, j);
    QuickSort(array, i, right);
}

// �迭�� ó�� 20���� ������ 20���� ���
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) {
        printf("%4d ", array[i]); // ó�� 20�� ���
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%4d ", array[i]); // ������ 20�� ���
    }
    printf("\n\n");
}

// ���� Ž�� �˰��� (Binary Search)
// �迭 ������ target ���� ã��, �� Ƚ���� ���
int binarySearch(int* array, int target, int* compareCount) {
    int left = 0, right = SIZE - 1;

    while (left <= right) {
        (*compareCount)++; // �� Ƚ�� ����
        int mid = (left + right) / 2; // �߰� �ε��� ���

        if (array[mid] == target) return mid; // �� ã��
        if (array[mid] < target)
            left = mid + 1; // ������ ���� Ž��
        else
            right = mid - 1; // ���� ���� Ž��
    }
    return -1; // ���� �迭�� ����
}

// ���������̼� Ž�� �˰��� (Interpolation Search)
// �迭 ������ target ���� ã��, �� Ƚ���� ���
int interpolationSearch(int* array, int target, int* compareCount) {
    int left = 0, right = SIZE - 1;

    while (left <= right && target >= array[left] && target <= array[right]) {
        (*compareCount)++; // �� Ƚ�� ����

        // Ž�� ��ġ ��� (��� ����)
        int pos = left + ((double)(right - left) / (array[right] - array[left]) * (target - array[left]));

        if (array[pos] == target) return pos; // �� ã��
        if (array[pos] < target)
            left = pos + 1; // ������ ���� Ž��
        else
            right = pos - 1; // ���� ���� Ž��
    }
    return -1; // ���� �迭�� ����
}

// ���� Ž���� ��� �� Ƚ���� ���
double getAverageBinarySearchCompareCount(int* array) {
    int totalCompareCount = 0;
    for (int i = 0; i < 1000; i++) { // 1000�� Ž�� ����
        int target = array[rand() % SIZE]; // �迭 �� ������ �� ����
        int compareCount = 0;
        binarySearch(array, target, &compareCount); // ���� Ž�� ����
        totalCompareCount += compareCount; // �� Ƚ�� ����
    }
    return (double)totalCompareCount / 1000; // ��� �� Ƚ�� ��ȯ
}

// ���������̼� Ž���� ��� �� Ƚ���� ���
double getAverageInterpolationSearchCompareCount(int* array) {
    int totalCompareCount = 0;
    for (int i = 0; i < 1000; i++) { // 1000�� Ž�� ����
        int target = array[rand() % SIZE]; // �迭 �� ������ �� ����
        int compareCount = 0;
        interpolationSearch(array, target, &compareCount); // ���������̼� Ž�� ����
        totalCompareCount += compareCount; // �� Ƚ�� ����
    }
    return (double)totalCompareCount / 1000; // ��� �� Ƚ�� ��ȯ
}

int main() {
    srand(time(NULL)); // ���� �õ� ����
    int array[SIZE];

    // 3�� �ݺ��Ͽ� ��� ���
    for (int i = 0; i < 3; i++) {
        generateRandomArray(array); // �迭 �ʱ�ȭ
        QuickSort(array, 0, SIZE - 1); // �迭 ����
        printArray(array); // �迭 ���

        // ���� Ž�� ��� �� Ƚ�� ���
        printf("Average Compare Count of Binary Search: %.2f\n", getAverageBinarySearchCompareCount(array));
        // ���������̼� Ž�� ��� �� Ƚ�� ���
        printf("Average Compare Count of Interpolation Search: %.2f\n", getAverageInterpolationSearchCompareCount(array));
    }

    return 0;
}