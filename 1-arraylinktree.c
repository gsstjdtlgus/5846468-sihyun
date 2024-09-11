#include <stdio.h>
#include <stdlib.h>

// Definition of TreeNode for linked tree
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to generate an array-based tree
void GenerateArrayTree(int* tree) {
    // Array representing the tree as shown in the image
    int list[] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

    // Fill the tree array with values from list
    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }

    // Print the tree array
    for (int i = 0; i < 15; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n");
}

// Array-based PreOrder Traversal
void ArrayPreOrder(int* tree, int index, int size) {
    if (index >= size) return;
    printf("%d ", tree[index]);
    ArrayPreOrder(tree, 2 * index + 1, size); // Left child index
    ArrayPreOrder(tree, 2 * index + 2, size); // Right child index
}

// Array-based InOrder Traversal
void ArrayInOrder(int* tree, int index, int size) {
    if (index >= size) return;
    ArrayInOrder(tree, 2 * index + 1, size); // Left child index
    printf("%d ", tree[index]);
    ArrayInOrder(tree, 2 * index + 2, size); // Right child index
}

// Array-based PostOrder Traversal
void ArrayPostOrder(int* tree, int index, int size) {
    if (index >= size) return;
    ArrayPostOrder(tree, 2 * index + 1, size); // Left child index
    ArrayPostOrder(tree, 2 * index + 2, size); // Right child index
    printf("%d ", tree[index]);
}

// Wrapper for array-based traversal
void ArrayOrder(int* tree) {
    printf("Array PreOrder: ");
    ArrayPreOrder(tree, 0, 15);
    printf("\n");

    printf("Array InOrder: ");
    ArrayInOrder(tree, 0, 15);
    printf("\n");

    printf("Array PostOrder: ");
    ArrayPostOrder(tree, 0, 15);
    printf("\n");
}

// Function to place a node in the linked tree
void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode;
    }
    else {
        node->right = newNode;
    }
}

// Function to generate a linked-list-based binary tree
void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2); // Left of root (node 1)
    PlaceNode(root, 1, 9); // Right of root (node 1)

    PlaceNode(root->left, 0, 3); // Left of node 2
    PlaceNode(root->left, 1, 5); // Right of node 2

    PlaceNode(root->right, 0, 10); // Left of node 9
    PlaceNode(root->right, 1, 13); // Right of node 9

    PlaceNode(root->left->left, 0, 4); // Left of node 3
    PlaceNode(root->left->left, 1, 6); // Right of node 3

    PlaceNode(root->left->right, 0, 7); // Left of node 5
    PlaceNode(root->left->right, 1, 8); // Right of node 5

    PlaceNode(root->right->left, 0, 11); // Left of node 10
    PlaceNode(root->right->left, 1, 12); // Right of node 10

    PlaceNode(root->right->right, 0, 14); // Left of node 13
    PlaceNode(root->right->right, 1, 15); // Right of node 13
}

// Linked-list-based PreOrder Traversal
void LinkPreOrder(TreeNode* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    LinkPreOrder(node->left);
    LinkPreOrder(node->right);
}

// Linked-list-based InOrder Traversal
void LinkInOrder(TreeNode* node) {
    if (node == NULL) return;
    LinkInOrder(node->left);
    printf("%d ", node->data);
    LinkInOrder(node->right);
}

// Linked-list-based PostOrder Traversal
void LinkPostOrder(TreeNode* node) {
    if (node == NULL) return;
    LinkPostOrder(node->left);
    LinkPostOrder(node->right);
    printf("%d ", node->data);
}

// Wrapper for linked-list-based traversal
void LinkOrders(TreeNode* root) {
    printf("Linked PreOrder: ");
    LinkPreOrder(root);
    printf("\n");

    printf("Linked InOrder: ");
    LinkInOrder(root);
    printf("\n");

    printf("Linked PostOrder: ");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int arr[15];
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = root->right = NULL;

    // Generate and print array-based tree
    GenerateArrayTree(arr);

    // Generate and print linked-list-based tree
    GenerateLinkTree(root);

    // Perform array-based traversals
    ArrayOrder(arr);

    // Perform linked-list-based traversals
    LinkOrders(root);

    return 0;
}