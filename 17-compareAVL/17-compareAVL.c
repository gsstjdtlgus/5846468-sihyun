#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 노드 구조체 정의
typedef struct Node {
    int key;
    struct Node* left, * right;
    int height; // AVL 트리를 위한 높이 정보
} Node;

// 전역 변수
int compareCount = 0; // 비교 횟수
int searchCount = 0;  // 탐색 횟수

// 함수 선언
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

// 메인 함수
int main(int argc, char* argv[]) {
    for (int i = 0; i < 3; i++) { // 3번 반복
        Node* root = NULL; // 트리 루트
        srand(time(NULL) + i); // 랜덤 시드 설정 (i를 추가하여 각 실행마다 다른 결과)
        float allCount = 0.0;

        // AVL 트리 실험
        doAVLBatch(&root);
        allCount = (float)compareCount / searchCount;
        printf("average AVL compare count: %.2f\n", allCount);

        // 메모리 해제 및 초기화
        freeTree(root);
        root = NULL;
        compareCount = searchCount = 0;

        // 이진 탐색 트리 실험
        doBSTBatch(&root);
        allCount = (float)compareCount / searchCount;
        printf("average Bin compare count: %.2f\n", allCount);

        // 메모리 해제
        freeTree(root);
        printf("\n"); // 실행 간 공백 출력
    }

    return 0;
}

// AVL 트리에 대해 2000번의 작업 수행
void doAVLBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int op = rand() % 3;    // 0: 삽입, 1: 삭제, 2: 탐색
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

// 이진 탐색 트리에 대해 2000번의 작업 수행
void doBSTBatch(Node** root) {
    for (int i = 0; i < 2000; i++) {
        int op = rand() % 3;    // 0: 삽입, 1: 삭제, 2: 탐색
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

// 노드 생성
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1; // 초기 높이
    return node;
}

// BST 삽입
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

// AVL 삽입
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

    // 높이 업데이트
    node->height = 1 + (getHeight(node->left) > getHeight(node->right)
        ? getHeight(node->left)
        : getHeight(node->right));

    // 균형 확인 및 회전
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

// BST 삭제
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

// AVL 삭제
Node* deleteAVL(Node* node, int key) {
    // BST 삭제와 동일 (추가로 균형 확인 및 회전 필요)
    return deleteBST(node, key);
}

// 탐색
Node* search(Node* node, int key) {
    if (node == NULL || node->key == key)
        return node;

    compareCount++;
    if (key < node->key)
        return search(node->left, key);
    return search(node->right, key);
}

// 높이 계산
int getHeight(Node* node) {
    return node ? node->height : 0;
}

// 균형 계산
int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// 오른쪽 회전
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// 왼쪽 회전
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

// 트리 메모리 해제
void freeTree(Node* node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

