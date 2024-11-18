#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// 랜덤 데이터 생성 함수
void generateRandomData(int data[]) {
    for (int i = 0; i < SIZE; i++) {
        data[i] = rand() % 1000;  // 0~999 사이의 값 생성
    }
}

// 선택 정렬 함수 (정렬 과정 출력 포함)
void doSelectionSort(int data[]) {
    int temp[SIZE];
    for (int i = 0; i < SIZE; i++) temp[i] = data[i];  // data 배열 복사

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

        // 정렬 과정을 10단위로 출력 (10, 20, ..., 마지막 단계)
        if ((i + 1) % 10 == 0 || i == SIZE - 2) {
            printf("Step %d: ", i + 1);
            for (int k = 0; k < SIZE; k++) {
                printf("%d ", temp[k]);
            }
            printf("\n");
        }
    }
}

// 삽입 정렬 함수 (20회 수행 후 평균 비교 횟수 계산)
void doInsertionSort(int data[]) {
    int totalCompareCount = 0;

    for (int t = 0; t < 20; t++) {  // 20회 수행
        generateRandomData(data);  // 매회 다른 랜덤 데이터를 생성
        int temp[SIZE];
        int compareCount = 0;
        for (int i = 0; i < SIZE; i++) temp[i] = data[i];  // data 배열 복사

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

    // 마지막 수행 결과 출력
    printf("Insertion Sort Result: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

// 버블 정렬 함수 (20회 수행 후 평균 이동 횟수 계산)
void doBubbleSort(int data[]) {
    int totalMoveCount = 0;

    for (int t = 0; t < 20; t++) {  // 20회 수행
        generateRandomData(data);  // 매회 다른 랜덤 데이터를 생성
        int temp[SIZE];
        int moveCount = 0;
        for (int i = 0; i < SIZE; i++) temp[i] = data[i];  // data 배열 복사

        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                if (temp[j] > temp[j + 1]) {
                    int tmp = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = tmp;
                    moveCount += 3;  // 각 swap마다 3번 이동
                }
            }
        }
        totalMoveCount += moveCount;
    }

    printf("\nBubble Sort Move Average: %d\n", totalMoveCount / 20);

    // 마지막 수행 결과 출력
    printf("Bubble Sort Result: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

// main 함수
int main() {
    int randomData[SIZE];
    srand(time(NULL));  // 매번 다른 랜덤 값을 생성하기 위해 시드 설정

    generateRandomData(randomData);  // 초기 랜덤 데이터 생성
    doSelectionSort(randomData);  // 선택 정렬 수행 및 과정 출력

    doInsertionSort(randomData);  // 삽입 정렬 20회 수행, 평균 비교 횟수 출력

    doBubbleSort(randomData);     // 버블 정렬 20회 수행, 평균 이동 횟수 출력

    return 0;
}
