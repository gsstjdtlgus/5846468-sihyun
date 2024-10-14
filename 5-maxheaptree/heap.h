#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ���� Ʈ�� ��� ����ü ����
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

// ���ο� ��带 �����ϰ� �ʱ�ȭ�ϴ� �Լ�
TreeNode* createNode(int data);

// �� ���� ��ȯ�ϴ� �Լ�
void swap(int* a, int* b);

// Ʈ���� ���� ������ ����ϴ� �Լ�
void printTree(TreeNode* root);

// �ִ� �� Ʈ���� ��带 �����ϴ� �Լ�
void InsertMaxHeapTree(TreeNode** root, int data, int* movements, bool showOutput);

// �ִ� �� Ʈ������ ��Ʈ ��带 �����ϴ� �Լ�
void deleteRoot(TreeNode** root, int* movements);

// Ʈ������ ������ ��带 ã�� �Լ�
TreeNode* findLastNode(TreeNode* root);

// Ʈ������ ��Ʈ ��带 ���� �� �������ϴ� �Լ�
void heapifyUp(TreeNode* node, int* movements, TreeNode* root);
void heapifyDown(TreeNode* node, int* movements, TreeNode* root);

// Ʈ�� ������ ��� �Լ�
void printLevelOrder(TreeNode* root);

// ����� �������̽� ���� �Լ�
void runUserInterface(TreeNode** root);

// Ʈ�� ���� �Լ�
TreeNode* GenerateMaxHeapTree(int inputData[], int size, int* movements);

#endif // HEAP_H
