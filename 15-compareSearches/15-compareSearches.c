#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000 // �迭�� ũ��

int compareCount; // ���� �� �� Ƚ���� �����ϴ� ���� ����

// ���� �迭 ���� �Լ�
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0���� 999 ������ ������ ���ڸ� �迭�� ����
    }
}

// ���� Ž�� �Լ�
int linearSearch(int* array, int target) {
    int count = 0; // �� Ƚ�� ī��Ʈ
    for (int i = 0; i < SIZE; i++) {
        count++;
        if (array[i] == target) break; // ���� ã���� Ž�� ����
    }
    return count; // �� Ƚ�� ��ȯ
}

// ���� Ž�� ��� �� Ƚ�� ��� �Լ�
float getAverageLinearSearchCompareCount(int* array) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // �迭���� �׻� �����ϴ� ���� Ÿ������ ����
        totalComparisons += linearSearch(array, target);
    }
    return totalComparisons / 100.0; // ��� �� Ƚ�� ��ȯ
}

// �� ������ ���� �Լ�
int partition(int* array, int low, int high) {
    int pivot = array[high]; // �ǹ� �� ���� (�迭�� ������ ��)
    int i = low - 1;
    for (int j = low; j < high; j++) {
        compareCount++; // �� Ƚ�� ����
        if (array[j] <= pivot) { // �ǹ����� ���� ���� �������� �̵�
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    // �ǹ��� ���ĵ� ��ġ�� ��ġ
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1; // �ǹ��� �ε��� ��ȯ
}

// �� ���� �Լ�
void quickSort(int* array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high); // ���� �۾� ����
        quickSort(array, low, pi - 1); // ���� �κ� �迭 ����
        quickSort(array, pi + 1, high); // ������ �κ� �迭 ����
    }
}

// �� ������ �����ϰ� �� Ƚ���� ����ϴ� �Լ�
void getQuickSortCompareCount(int* array) {
    compareCount = 0; // �� Ƚ�� �ʱ�ȭ
    quickSort(array, 0, SIZE - 1); // �� ���� ����
}

// ���� Ž�� �Լ�
int binarySearch(int* array, int target) {
    int low = 0, high = SIZE - 1, count = 0; // �ʱ�ȭ
    while (low <= high) {
        count++; // �� Ƚ�� ����
        int mid = (low + high) / 2; // �߰� �� ���
        if (array[mid] == target) return count; // ���� ã���� �� Ƚ�� ��ȯ
        else if (array[mid] < target) low = mid + 1; // ������ �κ� Ž��
        else high = mid - 1; // ���� �κ� Ž��
    }
    return count; // �� Ƚ�� ��ȯ
}

// ���� Ž�� ��� �� Ƚ�� ��� �Լ�
float getAverageBinarySearchCompareCount(int* array) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // �迭���� �׻� �����ϴ� ���� Ÿ������ ����
        totalComparisons += binarySearch(array, target);
    }
    return totalComparisons / 100.0; // ��� �� Ƚ�� ��ȯ
}

// �迭 ��� �Լ�
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) // �迭�� �� 20�� ���
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) // �迭�� �� 20�� ���
        printf("%3d ", array[i]);
    printf("\n");
}

// ���� �Լ�
int main(int argc, char* argv[]) {
    srand(time(NULL)); // ���� �õ� �ʱ�ȭ
    for (int run = 0; run < 3; run++) { // 3�� �ݺ� ����
        int array[SIZE]; // �迭 ����
        generateRandomArray(array); // ���� �迭 ����

        // ���� Ž�� ��� �� Ƚ�� ���
        printf("Average Linear Search Compare Count: %.2f\n",
            getAverageLinearSearchCompareCount(array));

        // �� ���� ���� �� �� Ƚ�� ���
        getQuickSortCompareCount(array);
        printf("Quick Sort Compare Count: %d\n", compareCount);

        // ���� Ž�� ��� �� Ƚ�� ���
        printf("Average Binary Search Compare Count: %.2f\n\n",
            getAverageBinarySearchCompareCount(array));

        // ���ĵ� �迭 ���
        printArray(array);

        printf("\n");
    }

    return 0;
}
