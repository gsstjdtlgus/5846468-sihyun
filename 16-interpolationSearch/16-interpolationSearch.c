#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000 // 배열 크기 정의

// 0부터 9999 사이의 임의의 숫자로 배열 초기화
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 10000; // 랜덤 값 생성
    }
}

// QuickSort 알고리즘 구현
void QuickSort(int* array, int left, int right) {
    if (left >= right) return; // 정렬 종료 조건

    int pivot = array[(left + right) / 2]; // 피벗 값 선택
    int i = left, j = right;

    // 피벗을 기준으로 배열 분할
    while (i <= j) {
        while (array[i] < pivot) i++;
        while (array[j] > pivot) j--;
        if (i <= j) {
            // 두 값을 교환
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }

    // 재귀적으로 분할 정렬 수행
    QuickSort(array, left, j);
    QuickSort(array, i, right);
}

// 배열의 처음 20개와 마지막 20개를 출력
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) {
        printf("%4d ", array[i]); // 처음 20개 출력
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%4d ", array[i]); // 마지막 20개 출력
    }
    printf("\n\n");
}

// 이진 탐색 알고리즘 (Binary Search)
// 배열 내에서 target 값을 찾고, 비교 횟수를 기록
int binarySearch(int* array, int target, int* compareCount) {
    int left = 0, right = SIZE - 1;

    while (left <= right) {
        (*compareCount)++; // 비교 횟수 증가
        int mid = (left + right) / 2; // 중간 인덱스 계산

        if (array[mid] == target) return mid; // 값 찾음
        if (array[mid] < target)
            left = mid + 1; // 오른쪽 절반 탐색
        else
            right = mid - 1; // 왼쪽 절반 탐색
    }
    return -1; // 값이 배열에 없음
}

// 인터폴레이션 탐색 알고리즘 (Interpolation Search)
// 배열 내에서 target 값을 찾고, 비교 횟수를 기록
int interpolationSearch(int* array, int target, int* compareCount) {
    int left = 0, right = SIZE - 1;

    while (left <= right && target >= array[left] && target <= array[right]) {
        (*compareCount)++; // 비교 횟수 증가

        // 탐색 위치 계산 (비례 분할)
        int pos = left + ((double)(right - left) / (array[right] - array[left]) * (target - array[left]));

        if (array[pos] == target) return pos; // 값 찾음
        if (array[pos] < target)
            left = pos + 1; // 오른쪽 절반 탐색
        else
            right = pos - 1; // 왼쪽 절반 탐색
    }
    return -1; // 값이 배열에 없음
}

// 이진 탐색의 평균 비교 횟수를 계산
double getAverageBinarySearchCompareCount(int* array) {
    int totalCompareCount = 0;
    for (int i = 0; i < 1000; i++) { // 1000번 탐색 수행
        int target = array[rand() % SIZE]; // 배열 내 임의의 값 선택
        int compareCount = 0;
        binarySearch(array, target, &compareCount); // 이진 탐색 수행
        totalCompareCount += compareCount; // 비교 횟수 누적
    }
    return (double)totalCompareCount / 1000; // 평균 비교 횟수 반환
}

// 인터폴레이션 탐색의 평균 비교 횟수를 계산
double getAverageInterpolationSearchCompareCount(int* array) {
    int totalCompareCount = 0;
    for (int i = 0; i < 1000; i++) { // 1000번 탐색 수행
        int target = array[rand() % SIZE]; // 배열 내 임의의 값 선택
        int compareCount = 0;
        interpolationSearch(array, target, &compareCount); // 인터폴레이션 탐색 수행
        totalCompareCount += compareCount; // 비교 횟수 누적
    }
    return (double)totalCompareCount / 1000; // 평균 비교 횟수 반환
}

int main() {
    srand(time(NULL)); // 랜덤 시드 설정
    int array[SIZE];

    // 3번 반복하여 결과 출력
    for (int i = 0; i < 3; i++) {
        generateRandomArray(array); // 배열 초기화
        QuickSort(array, 0, SIZE - 1); // 배열 정렬
        printArray(array); // 배열 출력

        // 이진 탐색 평균 비교 횟수 출력
        printf("Average Compare Count of Binary Search: %.2f\n", getAverageBinarySearchCompareCount(array));
        // 인터폴레이션 탐색 평균 비교 횟수 출력
        printf("Average Compare Count of Interpolation Search: %.2f\n", getAverageInterpolationSearchCompareCount(array));
    }

    return 0;
}