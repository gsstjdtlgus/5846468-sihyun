#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

// ���ο� ��带 �����ϰ� �ʱ�ȭ�ϴ� �Լ�
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// �� ���� ��ȯ�ϴ� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Ʈ���� ���� ������ ����ϴ� �Լ�
void printTree(TreeNode* root) {
    if (!root) return;

    TreeNode* queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];
        printf("%d ", current->data);

        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
    printf("\n");
}

// ���Ե� ��带 �ִ� �� Ư���� �����ϵ��� �θ�� ��ȯ�ϴ� �Լ�
void heapifyUp(TreeNode* node, int* movements, TreeNode* root) {
    while (node->parent && node->data > node->parent->data) {
        swap(&node->data, &node->parent->data);
        (*movements)++;
        printTree(root);  // Ʈ�� ��ü�� ���
        node = node->parent;
    }
}

// �� �ڽ� ��带 ���Ͽ� ���� �������ϴ� �Լ�
void heapifyDown(TreeNode* node, int* movements, TreeNode* root) {
    while (true) {
        TreeNode* largest = node;
        TreeNode* left = node->left;
        TreeNode* right = node->right;

        // ���� �ڽİ� ���Ͽ� �� ū �ڽ� ����
        if (left && left->data > largest->data)
            largest = left;

        // ������ �ڽİ� ���Ͽ� �� ū �ڽ� ����
        if (right && right->data > largest->data)
            largest = right;

        // �� ū �ڽİ� ���� ��带 ��ȯ
        if (largest != node) {
            swap(&node->data, &largest->data);  // �� ��ȯ
            (*movements)++;  // �̵� Ƚ�� ����
            printTree(root);  // Ʈ�� ���� ���
            node = largest;   // ���� ��带 �����Ͽ� ��� �� ������
        }
        else {
            break;  // �� �̻� ��ȯ�� �ʿ� ������ ����
        }
    }
}

// �ִ� �� Ʈ���� ��带 �����ϴ� �Լ�
void InsertMaxHeapTree(TreeNode** root, int data, int* movements, bool showOutput) {
    if (*root == NULL) {
        *root = createNode(data);
        if (showOutput) printTree(*root);
        return;
    }

    TreeNode* queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = *root;

    while (front < rear) {
        TreeNode* current = queue[front++];

        if (current->left == NULL) {
            current->left = createNode(data);
            current->left->parent = current;
            if (showOutput) printTree(*root);
            heapifyUp(current->left, movements, *root);
            break;
        }
        else {
            queue[rear++] = current->left;
        }

        if (current->right == NULL) {
            current->right = createNode(data);
            current->right->parent = current;
            if (showOutput) printTree(*root);
            heapifyUp(current->right, movements, *root);
            break;
        }
        else {
            queue[rear++] = current->right;
        }
    }
}

// Ʈ������ ������ ��带 ã�� �Լ�
TreeNode* findLastNode(TreeNode* root) {
    if (root == NULL) return NULL;

    TreeNode* queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = root;
    TreeNode* last = NULL;

    while (front < rear) {
        last = queue[front++];

        if (last->left) queue[rear++] = last->left;
        if (last->right) queue[rear++] = last->right;
    }

    return last;
}

// �ִ� �� Ʈ������ ��Ʈ ��带 �����ϴ� �Լ�
void deleteRoot(TreeNode** root, int* movements) {
    if (*root == NULL) {
        printf("Ʈ���� ��� �ֽ��ϴ�.\n");
        return;
    }

    TreeNode* lastNode = findLastNode(*root);  // ������ ��带 ã��
    if (lastNode == *root) {  // Ʈ���� ��尡 �ϳ��ۿ� ������
        free(*root);
        *root = NULL;
        return;
    }

    // ������ ���� ��Ʈ ��带 ��ȯ�� �� ������ ��带 ����
    swap(&(*root)->data, &lastNode->data);
    (*movements)++;  // ��Ʈ�� ������ ����� �� ��ȯ �� �̵� Ƚ�� ����

    if (lastNode->parent->left == lastNode)
        lastNode->parent->left = NULL;
    else
        lastNode->parent->right = NULL;

    free(lastNode);

    // ��Ʈ�������� �� ������
    printTree(*root);
    heapifyDown(*root, movements, *root);
}

// Ʈ�� ������ ��� �Լ�
void printLevelOrder(TreeNode* root) {
    if (root == NULL) {
        printf("Ʈ���� ��� �ֽ��ϴ�.\n");
        return;
    }

    TreeNode* queue[1000];
    int level[1000];
    int front = 0, rear = 0;

    queue[rear] = root;
    level[rear++] = 1;

    int currentLevel = 1;

    printf("[%d] ", currentLevel);

    // ť�� ����Ͽ� �������� Ʈ���� ���
    while (front < rear) {
        TreeNode* current = queue[front];
        int nodeLevel = level[front++];

        if (nodeLevel > currentLevel) {
            currentLevel = nodeLevel;
            printf("\n[%d] ", currentLevel);
        }

        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[rear] = current->left;
            level[rear++] = nodeLevel + 1;
        }
        if (current->right != NULL) {
            queue[rear] = current->right;
            level[rear++] = nodeLevel + 1;
        }
    }
    printf("\n");
}

// Ʈ�� ���� �Լ�
TreeNode* GenerateMaxHeapTree(int inputData[], int size, int* movements) {
    TreeNode* root = NULL;

    for (int i = 0; i < size; i++) {
        InsertMaxHeapTree(&root, inputData[i], movements, false);
    }

    return root;
}