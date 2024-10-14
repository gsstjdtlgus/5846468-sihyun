#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#pragma warning(disable:4996)

// 사용자 인터페이스 실행 함수
void runUserInterface(TreeNode** root) {
    while (true) {
        char choice;
        int data, movements;
        printf("---------------------\n");
        printf("| i : 노드 추가     |\n");
        printf("| d : 루트 삭제     |\n");
        printf("| p : 레벨별 출력   |\n");
        printf("| c : 종료          |\n");
        printf("---------------------\n\n");
        printf("메뉴 입력: ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'i':  // 노드 추가
            printf("추가할 값 입력: ");
            scanf("%d", &data);
            movements = 0;
            InsertMaxHeapTree(root, data, &movements, true);
            printf("노드가 이동된 횟수: %d\n", movements);
            break;
        case 'd':  // 루트 노드 삭제
            movements = 0;
            deleteRoot(root, &movements);
            printf("노드가 이동된 횟수: %d\n", movements);
            break;
        case 'p':  // 트리 레벨별 출력
            printf("트리 레벨별 출력\n");
            printLevelOrder(*root);
            break;
        case 'c':  // 프로그램 종료
            exit(0);
            break;
        default:
            printf("잘못된 선택입니다.\n");
        }
    }
}

// 메인 함수
int main() {
    // 초기 데이터를 이용해 트리 생성
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int size = sizeof(inputData) / sizeof(inputData[0]);
    int movements = 0;

    TreeNode* root = GenerateMaxHeapTree(inputData, size, &movements);

    // 사용자 인터페이스 실행
    runUserInterface(&root);

    // 메모리 해제
    free(root);

    return 0;
}
