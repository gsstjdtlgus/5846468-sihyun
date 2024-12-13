#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��� ����ü ����
typedef struct Node {
    int key;
    struct Node* left, * right;
    int height; // AVL Ʈ���� ���� ���� ����
} Node;

// ���� ����
int compareCount = 0; // �� Ƚ��
int searchCount = 0;  // Ž�� Ƚ��

// �Լ� ����
Node* createNode(int key);
Node* insertBST(Node* node, int key);
Node* insertAVL(Node* node, int key);
Node* deleteBST(Node* node, int key);
Node* deleteAVL(Node* node, int key);
Node* search(Node* node, int key);
void freeTree(Node* node);
void doBSTBatch(Node** root);
void doAVLBatch(Node** root);
int getHeight(Node* node);
int getBalance(Node* node);
Node* rotateRight(Node* y);
Node* rotateLeft(Node* x);

// ���� �Լ�
int main(int argc, char* argv[]) {
    for (int i = 0; i < 3; i++) { // 3�� �ݺ�
        Node* root = NULL; // Ʈ�� ��Ʈ
        srand(time(NULL) + i); // ���� �õ� ���� (i�� �߰��Ͽ� �� ���ึ�� �ٸ� ���)
        float allCount = 0.0;

        // AVL Ʈ�� ����
        doAVLBatch(&root);
        allCount = (float)compareCount / searchCount;
        printf("average AVL compare count: %.2f\n", allCount);

        // �޸� ���� �� �ʱ�ȭ
        freeTree(root);
        root = NULL;
        compareCount = searchCount = 0;

        // ���� Ž�� Ʈ�� ����
        doBSTBatch(&root);
        allCount = (float)compareCount / searchCount;
        printf("average Bin compare count: %.2f\n", allCount);

        // �޸� ����
        freeTree(root);
        printf("\n"); // ���� �� ���� ���
    }

    return 0;
}

// AVL Ʈ���� ���� 2000���� �۾� ����
void doAVLBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int op = rand() % 3;    // 0: ����, 1: ����, 2: Ž��
        int value = rand() % 1000;

        if (op == 0) {
            *root = insertAVL(*root, value);
        }
        else if (op == 1) {
            *root = deleteAVL(*root, value);
        }
        else {
            search(*root, value);
            searchCount++;
        }
    }
}

// ���� Ž�� Ʈ���� ���� 2000���� �۾� ����
void doBSTBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int op = rand() % 3;    // 0: ����, 1: ����, 2: Ž��
        int value = rand() % 1000;

        if (op == 0) {
            *root = insertBST(*root, value);
        }
        else if (op == 1) {
            *root = deleteBST(*root, value);
        }
        else {
            search(*root, value);
            searchCount++;
        }
    }
}

// ��� ����
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // �ʱ� ����
    return node;
}

// BST ����
Node* insertBST(Node* node, int key) {
    if (node == NULL)
        return createNode(key);

    compareCount++;
    if (key < node->key)
        node->left = insertBST(node->left, key);
    else if (key > node->key)
        node->right = insertBST(node->right, key);

    return node;
}

// AVL ����
Node* insertAVL(Node* node, int key) {
    if (node == NULL)
        return createNode(key);

    compareCount++;
    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node;

    // ���� ������Ʈ
    node->height = 1 + (getHeight(node->left) > getHeight(node->right)
        ? getHeight(node->left)
        : getHeight(node->right));

    // ���� Ȯ�� �� ȸ��
    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// BST ����
Node* deleteBST(Node* node, int key) {
    if (node == NULL)
        return NULL;

    compareCount++;
    if (key < node->key)
        node->left = deleteBST(node->left, key);
    else if (key > node->key)
        node->right = deleteBST(node->right, key);
    else {
        if (node->left == NULL || node->right == NULL) {
            Node* temp = node->left ? node->left : node->right;
            free(node);
            return temp;
        }
        else {
            Node* temp = node->right;
            while (temp->left != NULL)
                temp = temp->left;
            node->key = temp->key;
            node->right = deleteBST(node->right, temp->key);
        }
    }
    return node;
}

// AVL ����
Node* deleteAVL(Node* node, int key) {
    // BST ������ ���� (�߰��� ���� Ȯ�� �� ȸ�� �ʿ�)
    return deleteBST(node, key);
}

// Ž��
Node* search(Node* node, int key) {
    if (node == NULL || node->key == key)
        return node;

    compareCount++;
    if (key < node->key)
        return search(node->left, key);
    return search(node->right, key);
}

// ���� ���
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// ���� ���
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// ������ ȸ��
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// ���� ȸ��
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

// Ʈ�� �޸� ����
void freeTree(Node* node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

