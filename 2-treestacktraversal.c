#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

// 스택 관련 함수들
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

// 노드를 배치하는 함수
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

// 트리를 생성하는 함수
void GenerateLinkTree(TreeNode* root) {
    if (root == NULL) {
        printf("Error: Root is NULL.\n");
        return;
    }

    PlaceNode(root, 0, 2);      // 루트의 왼쪽에 2
    if (root->left != NULL) {
        PlaceNode(root->left, 0, 3); // 2의 왼쪽에 3
        PlaceNode(root->left, 1, 5); // 2의 오른쪽에 5
        if (root->left->left != NULL) {
            PlaceNode(root->left->left, 0, 4); // 3의 왼쪽에 4
        }
        if (root->left->right != NULL) {
            PlaceNode(root->left->right, 0, 6); // 5의 왼쪽에 6
            PlaceNode(root->left->right, 1, 7); // 5의 오른쪽에 7
        }
    }
    PlaceNode(root, 1, 9);      // 루트의 오른쪽에 9
    if (root->right != NULL) {
        PlaceNode(root->right, 0, 10); // 9의 왼쪽에 10
        if (root->right->left != NULL) {
            PlaceNode(root->right->left, 1, 11); // 10의 오른쪽에 11
        }
        PlaceNode(root->right, 1, 13); // 9의 오른쪽에 13
        if (root->right->right != NULL) {
            PlaceNode(root->right->right, 1, 15); // 13의 오른쪽에 15
        }
    }
}

// 전위 순회 (Pre-order traversal)
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

// 중위 순회 (In-order traversal)
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

// 후위 순회 (Post-order traversal)
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

// 트리 순회 함수 호출
void LinkOrders(TreeNode* root) {
    printf("Pre-order traversal:\n");
    LinkPreOrder(root);

    printf("In-order traversal:\n");
    LinkInOrder(root);

    printf("Post-order traversal:\n");
    LinkPostOrder(root);
}

// main 함수
int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    if (root == NULL) {
        printf("Error: Could not allocate memory for root.\n");
        return -1;
    }
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    // 각각의 방식(array법, link법)에 따른 트리 생성
    GenerateLinkTree(root);

    // 생성한 트리를 스택 반복방식으로 순회
    LinkOrders(root);

    return 0;
}

