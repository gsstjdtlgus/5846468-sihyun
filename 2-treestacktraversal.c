#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

// ���� ���� �Լ���
StackNode* createStackNode(TreeNode* treeNode) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    return newNode;
}

int isEmpty(StackNode* root) {
    return !root;
}

void push(StackNode** root, TreeNode* treeNode) {
    StackNode* stackNode = createStackNode(treeNode);
    stackNode->next = *root;
    *root = stackNode;
    printf("push(%d) ", treeNode->data);
}

TreeNode* pop(StackNode** root) {
    if (isEmpty(*root)) {
        return NULL;
    }
    StackNode* temp = *root;
    *root = (*root)->next;
    TreeNode* popped = temp->treeNode;
    free(temp);
    printf("pop(%d) ", popped->data);
    return popped;
}

// ��带 ��ġ�ϴ� �Լ�
void PlaceNode(TreeNode* node, int direction, int data) {
    if (node == NULL) {
        printf("Error: Cannot place node, parent node is NULL.\n");
        return;
    }

    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed for new node.\n");
        return;
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
        if (node->left != NULL) {
            printf("Error: Left child already exists for node %d.\n", node->data);
        }
        else {
            node->left = newNode;
        }
    }
    else if (direction == 1) {
        if (node->right != NULL) {
            printf("Error: Right child already exists for node %d.\n", node->data);
        }
        else {
            node->right = newNode;
        }
    }
}

// Ʈ���� �����ϴ� �Լ�
void GenerateLinkTree(TreeNode* root) {
    if (root == NULL) {
        printf("Error: Root is NULL.\n");
        return;
    }

    PlaceNode(root, 0, 2);      // ��Ʈ�� ���ʿ� 2
    if (root->left != NULL) {
        PlaceNode(root->left, 0, 3); // 2�� ���ʿ� 3
        PlaceNode(root->left, 1, 5); // 2�� �����ʿ� 5
        if (root->left->left != NULL) {
            PlaceNode(root->left->left, 0, 4); // 3�� ���ʿ� 4
        }
        if (root->left->right != NULL) {
            PlaceNode(root->left->right, 0, 6); // 5�� ���ʿ� 6
            PlaceNode(root->left->right, 1, 7); // 5�� �����ʿ� 7
        }
    }
    PlaceNode(root, 1, 9);      // ��Ʈ�� �����ʿ� 9
    if (root->right != NULL) {
        PlaceNode(root->right, 0, 10); // 9�� ���ʿ� 10
        if (root->right->left != NULL) {
            PlaceNode(root->right->left, 1, 11); // 10�� �����ʿ� 11
        }
        PlaceNode(root->right, 1, 13); // 9�� �����ʿ� 13
        if (root->right->right != NULL) {
            PlaceNode(root->right->right, 1, 15); // 13�� �����ʿ� 15
        }
    }
}

// ���� ��ȸ (Pre-order traversal)
void LinkPreOrder(TreeNode* root) {
    if (root == NULL) return;

    StackNode* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        TreeNode* node = pop(&stack);
        printf("visit(%d) ", node->data);

        if (node->right) push(&stack, node->right);
        if (node->left) push(&stack, node->left);
    }
    printf("\n");
}

// ���� ��ȸ (In-order traversal)
void LinkInOrder(TreeNode* root) {
    StackNode* stack = NULL;
    TreeNode* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("visit(%d) ", current->data);
        current = current->right;
    }
    printf("\n");
}

// ���� ��ȸ (Post-order traversal)
void LinkPostOrder(TreeNode* root) {
    if (root == NULL) return;

    StackNode* s1 = NULL, * s2 = NULL;
    push(&s1, root);

    while (!isEmpty(s1)) {
        TreeNode* node = pop(&s1);
        push(&s2, node);

        if (node->left) push(&s1, node->left);
        if (node->right) push(&s1, node->right);
    }

    while (!isEmpty(s2)) {
        TreeNode* node = pop(&s2);
        printf("visit(%d) ", node->data);
    }
    printf("\n");
}

// Ʈ�� ��ȸ �Լ� ȣ��
void LinkOrders(TreeNode* root) {
    printf("Pre-order traversal:\n");
    LinkPreOrder(root);

    printf("In-order traversal:\n");
    LinkInOrder(root);

    printf("Post-order traversal:\n");
    LinkPostOrder(root);
}

// main �Լ�
int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    if (root == NULL) {
        printf("Error: Could not allocate memory for root.\n");
        return -1;
    }
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    // ������ ���(array��, link��)�� ���� Ʈ�� ����
    GenerateLinkTree(root);

    // ������ Ʈ���� ���� �ݺ�������� ��ȸ
    LinkOrders(root);

    return 0;
}

