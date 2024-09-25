#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef struct QueueNode {
    TreeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* CreateQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void Enqueue(Queue* q, TreeNode* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->treeNode = node;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

TreeNode* Dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    QueueNode* temp = q->front;
    TreeNode* treeNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return treeNode;
}

int IsQueueEmpty(Queue* q) {
    return q->front == NULL;
}

TreeNode* CreateNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void PlaceNode(TreeNode* node, int direction, int data) {
    if (direction == 0) {
        node->left = CreateNode(data);
    }
    else if (direction == 1) {
        node->right = CreateNode(data);
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 3);

    PlaceNode(root->left, 0, 4);
    PlaceNode(root->left, 1, 5);

    PlaceNode(root->right, 0, 6);
    PlaceNode(root->right, 1, 7);

    PlaceNode(root->left->left, 0, 8);
    PlaceNode(root->left->left, 1, 9);

    PlaceNode(root->left->right, 0, 10);
    PlaceNode(root->left->right, 1, 11);

    PlaceNode(root->right->left, 0, 12);
    PlaceNode(root->right->left, 1, 13);

    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

int GetSumOfNodes(TreeNode* root) {
    int sum = 0;
    Queue* q = CreateQueue();
    Enqueue(q, root);

    while (!IsQueueEmpty(q)) {
        TreeNode* current = Dequeue(q);
        sum += current->data;

        if (current->left) Enqueue(q, current->left);
        if (current->right) Enqueue(q, current->right);
    }

    return sum;
}

int GetNumberOfNodes(TreeNode* root) {
    int count = 0;
    Queue* q = CreateQueue();
    Enqueue(q, root);

    while (!IsQueueEmpty(q)) {
        TreeNode* current = Dequeue(q);
        count++;

        if (current->left) Enqueue(q, current->left);
        if (current->right) Enqueue(q, current->right);
    }

    return count;
}

int GetHeightOfTree(TreeNode* root) {
    if (root == NULL) return 0;

    Queue* q = CreateQueue();
    Enqueue(q, root);
    int height = 0;

    while (!IsQueueEmpty(q)) {
        int nodeCount = 0;
        Queue* levelQueue = CreateQueue();

        while (!IsQueueEmpty(q)) {
            TreeNode* node = Dequeue(q);
            nodeCount++;
            if (node->left) Enqueue(levelQueue, node->left);
            if (node->right) Enqueue(levelQueue, node->right);
        }

        if (nodeCount > 0) height++;
        q = levelQueue;
    }
    return height;
}

int GetNumberOfLeafNodes(TreeNode* root) {
    int leafCount = 0;
    Queue* q = CreateQueue();
    Enqueue(q, root);

    while (!IsQueueEmpty(q)) {
        TreeNode* current = Dequeue(q);

        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }

        if (current->left) Enqueue(q, current->left);
        if (current->right) Enqueue(q, current->right);
    }

    return leafCount;
}
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef struct QueueNode {
    TreeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* CreateQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void Enqueue(Queue* q, TreeNode* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->treeNode = node;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

TreeNode* Dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    QueueNode* temp = q->front;
    TreeNode* treeNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return treeNode;
}

int IsQueueEmpty(Queue* q) {
    return q->front == NULL;
}

TreeNode* CreateNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void PlaceNode(TreeNode* node, int direction, int data) {
    if (direction == 0) {
        node->left = CreateNode(data);
    }
    else if (direction == 1) {
        node->right = CreateNode(data);
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 3);

    PlaceNode(root->left, 0, 4);
    PlaceNode(root->left, 1, 5);

    PlaceNode(root->right, 0, 6);
    PlaceNode(root->right, 1, 7);

    PlaceNode(root->left->left, 0, 8);
    PlaceNode(root->left->left, 1, 9);

    PlaceNode(root->left->right, 0, 10);
    PlaceNode(root->left->right, 1, 11);

    PlaceNode(root->right->left, 0, 12);
    PlaceNode(root->right->left, 1, 13);

    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

int GetSumOfNodes(TreeNode* root) {
    int sum = 0;
    Queue* q = CreateQueue();
    Enqueue(q, root);

    while (!IsQueueEmpty(q)) {
        TreeNode* current = Dequeue(q);
        sum += current->data;

        if (current->left) Enqueue(q, current->left);
        if (current->right) Enqueue(q, current->right);
    }

    return sum;
}

int GetNumberOfNodes(TreeNode* root) {
    int count = 0;
    Queue* q = CreateQueue();
    Enqueue(q, root);

    while (!IsQueueEmpty(q)) {
        TreeNode* current = Dequeue(q);
        count++;

        if (current->left) Enqueue(q, current->left);
        if (current->right) Enqueue(q, current->right);
    }

    return count;
}

int GetHeightOfTree(TreeNode* root) {
    if (root == NULL) return 0;

    Queue* q = CreateQueue();
    Enqueue(q, root);
    int height = 0;

    while (!IsQueueEmpty(q)) {
        int nodeCount = 0;
        Queue* levelQueue = CreateQueue();

        while (!IsQueueEmpty(q)) {
            TreeNode* node = Dequeue(q);
            nodeCount++;
            if (node->left) Enqueue(levelQueue, node->left);
            if (node->right) Enqueue(levelQueue, node->right);
        }

        if (nodeCount > 0) height++;
        q = levelQueue;
    }
    return height;
}

int GetNumberOfLeafNodes(TreeNode* root) {
    int leafCount = 0;
    Queue* q = CreateQueue();
    Enqueue(q, root);

    while (!IsQueueEmpty(q)) {
        TreeNode* current = Dequeue(q);

        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }

        if (current->left) Enqueue(q, current->left);
        if (current->right) Enqueue(q, current->right);
    }

    return leafCount;
}

#include <stdio.h>
#include "tree.h"

int main() {
    TreeNode* root = CreateNode(1);

    // Create the binary tree structure
    GenerateLinkTree(root);

    // 1. Sum of all nodes
    printf("Sum of nodes: %d\n", GetSumOfNodes(root));

    // 2. Total number of nodes
    printf("Number of nodes: %d\n", GetNumberOfNodes(root));

    // 3. Height of the tree
    printf("Height of tree: %d\n", GetHeightOfTree(root));

    // 4. Number of leaf nodes
    printf("Number of leaf nodes: %d\n", GetNumberOfLeafNodes(root));

    return 0;
}
