#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct ThreadNode {
    int data;
    struct ThreadNode* left, * right;
    int leftThread, rightThread;
} ThreadNode;


TreeNode* createTreeNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


TreeNode* insert(TreeNode* node, int data) {
    if (node == NULL) return createTreeNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else
        node->right = insert(node->right, data);

    return node;
}


TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert(root, inputData[i]);
    }
    return root;
}


void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}


ThreadNode* previous = NULL;

ThreadNode* createThreadNode(int data) {
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->leftThread = 0;
    newNode->rightThread = 0;
    return newNode;
}


void createThreaded(TreeNode* root, ThreadNode** tRoot) {
    if (root == NULL) return;

    createThreaded(root->left, tRoot);

    ThreadNode* newNode = createThreadNode(root->data);
    if (*tRoot == NULL) {
        *tRoot = newNode;
    }
    if (previous != NULL) {
        previous->right = newNode;
        previous->rightThread = 1;
    }
    previous = newNode;

    createThreaded(root->right, tRoot);
}


ThreadNode* GenerateThreadTree(TreeNode* root) {
    ThreadNode* tRoot = NULL;
    previous = NULL;
    createThreaded(root, &tRoot);
    return tRoot;
}


void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;
    while (current != NULL) {
        while (current->left != NULL) {
            current = current->left;
        }

        printf("%d ", current->data);

        while (current->rightThread) {
            current = current->right;
            printf("%d ", current->data);
        }
        current = current->right;
    }
}

// main ÇÔ¼ö
int main() {
    int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = GenerateBinaryTree(inputData, size);

    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode* troot = GenerateThreadTree(root);

    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    free(root);
    free(troot);

    return 0;
}
