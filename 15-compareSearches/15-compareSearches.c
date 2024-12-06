#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000 // 배열의 크기

int compareCount; // 정렬 시 비교 횟수를 저장하는 전역 변수

// 랜덤 배열 생성 함수
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0부터 999 사이의 임의의 숫자를 배열에 저장
    }
}

// 순차 탐색 함수
int linearSearch(int* array, int target) {
    int count = 0; // 비교 횟수 카운트
    for (int i = 0; i < SIZE; i++) {
        count++;
        if (array[i] == target) break; // 값을 찾으면 탐색 종료
    }
    return count; // 비교 횟수 반환
}

// 순차 탐색 평균 비교 횟수 계산 함수
float getAverageLinearSearchCompareCount(int* array) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // 배열에서 항상 존재하는 값을 타겟으로 설정
        totalComparisons += linearSearch(array, target);
    }
    return totalComparisons / 100.0; // 평균 비교 횟수 반환
}

// 퀵 정렬의 분할 함수
int partition(int* array, int low, int high) {
    int pivot = array[high]; // 피벗 값 설정 (배열의 마지막 값)
    int i = low - 1;
    for (int j = low; j < high; j++) {
        compareCount++; // 비교 횟수 증가
        if (array[j] <= pivot) { // 피벗보다 작은 값을 왼쪽으로 이동
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    // 피벗을 정렬된 위치에 배치
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1; // 피벗의 인덱스 반환
}

// 퀵 정렬 함수
void quickSort(int* array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high); // 분할 작업 수행
        quickSort(array, low, pi - 1); // 왼쪽 부분 배열 정렬
        quickSort(array, pi + 1, high); // 오른쪽 부분 배열 정렬
    }
}

// 퀵 정렬을 수행하고 비교 횟수를 계산하는 함수
void getQuickSortCompareCount(int* array) {
    compareCount = 0; // 비교 횟수 초기화
    quickSort(array, 0, SIZE - 1); // 퀵 정렬 수행
}

// 이진 탐색 함수
int binarySearch(int* array, int target) {
    int low = 0, high = SIZE - 1, count = 0; // 초기화
    while (low <= high) {
        count++; // 비교 횟수 증가
        int mid = (low + high) / 2; // 중간 값 계산
        if (array[mid] == target) return count; // 값을 찾으면 비교 횟수 반환
        else if (array[mid] < target) low = mid + 1; // 오른쪽 부분 탐색
        else high = mid - 1; // 왼쪽 부분 탐색
    }
    return count; // 비교 횟수 반환
}

// 이진 탐색 평균 비교 횟수 계산 함수
float getAverageBinarySearchCompareCount(int* array) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // 배열에서 항상 존재하는 값을 타겟으로 설정
        totalComparisons += binarySearch(array, target);
    }
    return totalComparisons / 100.0; // 평균 비교 횟수 반환
}

// 배열 출력 함수
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) // 배열의 앞 20개 출력
        printf("%3d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) // 배열의 뒤 20개 출력
        printf("%3d ", array[i]);
    printf("\n");
}

// 메인 함수
int main(int argc, char* argv[]) {
    srand(time(NULL)); // 랜덤 시드 초기화
    for (int run = 0; run < 3; run++) { // 3번 반복 실행
        int array[SIZE]; // 배열 선언
        generateRandomArray(array); // 랜덤 배열 생성

        // 순차 탐색 평균 비교 횟수 출력
        printf("Average Linear Search Compare Count: %.2f\n",
            getAverageLinearSearchCompareCount(array));

        // 퀵 정렬 수행 및 비교 횟수 출력
        getQuickSortCompareCount(array);
        printf("Quick Sort Compare Count: %d\n", compareCount);

        // 이진 탐색 평균 비교 횟수 출력
        printf("Average Binary Search Compare Count: %.2f\n\n",
            getAverageBinarySearchCompareCount(array));

        // 정렬된 배열 출력
        printArray(array);

        printf("\n");
    }

    return 0;
}
