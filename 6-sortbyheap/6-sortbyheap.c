#include <stdio.h>
#include <stdlib.h>

// 두 정수를 포인터를 통해 교환하는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 배열의 요소를 출력하는 함수
void printArray(int inputData[], int n) {
    for (int j = 0; j < n; j++) {
        printf("%d ", inputData[j]);
    }
    printf("\n");
}

// 인덱스 i를 루트로 하는 서브트리의 힙 속성을 유지하는 함수
void resortHeap(int inputData[], int n, int i) {
    int largest = i; // 루트를 largest로 초기화
    int left = 2 * i + 1; // 왼쪽 자식의 인덱스
    int right = 2 * i + 2; // 오른쪽 자식의 인덱스

    // 왼쪽 자식이 루트보다 크면
    if (left < n && inputData[left] > inputData[largest]) {
        largest = left;
    }

    // 오른쪽 자식이 지금까지의 largest보다 크면
    if (right < n && inputData[right] > inputData[largest]) {
        largest = right;
    }

    // largest가 루트가 아니라면, 교환하고 계속 힙화
    if (largest != i) {
        swap(&inputData[i], &inputData[largest]);
        resortHeap(inputData, n, largest);
    }
}

// 배열로부터 최대 힙을 구축하는 함수
void BuildMaxHeap(int inputData[], int n) {
    int startIdx = n / 2 - 1; // 마지막 비리프 노드에서 시작
    for (int i = startIdx; i >= 0; i--) {
        resortHeap(inputData, n, i);
    }
}

// 입력 배열에 대해 힙 정렬을 수행하는 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    // 최대 힙을 구축하고 중간 상태를 출력
    for (int i = 0; i < n; i++) {
        BuildMaxHeap(inputData, i + 1);
        printArray(inputData, i + 1);  // 현재 배열 상태 출력
    }

    // 힙에서 요소를 하나씩 추출하여 배열을 정렬
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]); // 현재 루트를 끝으로 이동
        resortHeap(inputData, i, 0); // 축소된 힙에 대해 최대 힙화 호출

        // 정렬된 부분의 현재 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

// 힙 정렬을 실행하는 메인 함수
int main(void) {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]); // 배열의 크기 계산

    printf("<Sort>\n"); // 정렬 과정 시작 알림
    BuildMaxHeapAndSort(inputData, size); // 힙 정렬 수행

    printf("\nSorted Array:\n"); // 최종 정렬된 배열 출력
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0; // 성공적인 완료를 나타냄
}

