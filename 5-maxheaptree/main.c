#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"
#pragma warning(disable:4996)

// ����� �������̽� ���� �Լ�
void runUserInterface(TreeNode** root) {
    while (true) {
        char choice;
        int data, movements;
        printf("---------------------\n");
        printf("| i : ��� �߰�     |\n");
        printf("| d : ��Ʈ ����     |\n");
        printf("| p : ������ ���   |\n");
        printf("| c : ����          |\n");
        printf("---------------------\n\n");
        printf("�޴� �Է�: ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'i':  // ��� �߰�
            printf("�߰��� �� �Է�: ");
            scanf("%d", &data);
            movements = 0;
            InsertMaxHeapTree(root, data, &movements, true);
            printf("��尡 �̵��� Ƚ��: %d\n", movements);
            break;
        case 'd':  // ��Ʈ ��� ����
            movements = 0;
            deleteRoot(root, &movements);
            printf("��尡 �̵��� Ƚ��: %d\n", movements);
            break;
        case 'p':  // Ʈ�� ������ ���
            printf("Ʈ�� ������ ���\n");
            printLevelOrder(*root);
            break;
        case 'c':  // ���α׷� ����
            exit(0);
            break;
        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    }
}

// ���� �Լ�
int main() {
    // �ʱ� �����͸� �̿��� Ʈ�� ����
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
    int size = sizeof(inputData) / sizeof(inputData[0]);
    int movements = 0;

    TreeNode* root = GenerateMaxHeapTree(inputData, size, &movements);

    // ����� �������̽� ����
    runUserInterface(&root);

    // �޸� ����
    free(root);

    return 0;
}
