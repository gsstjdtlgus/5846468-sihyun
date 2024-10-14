#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 이진 트리 노드 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

// 새로운 노드를 생성하고 초기화하는 함수
TreeNode* createNode(int data);

// 두 값을 교환하는 함수
void swap(int* a, int* b);

// 트리를 레벨 순서로 출력하는 함수
void printTree(TreeNode* root);

// 최대 힙 트리에 노드를 삽입하는 함수
void InsertMaxHeapTree(TreeNode** root, int data, int* movements, bool showOutput);

// 최대 힙 트리에서 루트 노드를 삭제하는 함수
void deleteRoot(TreeNode** root, int* movements);

// 트리에서 마지막 노드를 찾는 함수
TreeNode* findLastNode(TreeNode* root);

// 트리에서 루트 노드를 삭제 후 재정렬하는 함수
void heapifyUp(TreeNode* node, int* movements, TreeNode* root);
void heapifyDown(TreeNode* node, int* movements, TreeNode* root);

// 트리 레벨별 출력 함수
void printLevelOrder(TreeNode* root);

// 사용자 인터페이스 실행 함수
void runUserInterface(TreeNode** root);

// 트리 생성 함수
TreeNode* GenerateMaxHeapTree(int inputData[], int size, int* movements);

#endif // HEAP_H
