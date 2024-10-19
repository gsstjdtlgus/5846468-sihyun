#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char character;
    int frequency;
    struct Node* left;
    struct Node* right;
} Node;

// 우선순위 큐의 노드를 위한 비교 함수
int compare(const void* a, const void* b) {
    return ((Node*)a)->frequency - ((Node*)b)->frequency;
}

// 노드 생성 함수
Node* createNode(char character, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Huffman 트리를 구축하는 함수
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node** nodes = (Node**)malloc(size * sizeof(Node*));

    // 노드 배열 초기화
    for (int i = 0; i < size; i++) {
        nodes[i] = createNode(characters[i], frequencies[i]);
    }

    // 우선순위 큐를 사용하여 최소 힙을 유지
    qsort(nodes, size, sizeof(Node*), compare);

    // 트리 구축
    while (size > 1) {
        // 두 개의 가장 작은 노드 선택
        Node* left = nodes[0];
        Node* right = nodes[1];

        // 새로운 노드 생성
        Node* newNode = createNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        // 새 노드를 배열에 추가하고 정렬
        nodes[1] = newNode; // 두 번째 자리에 새로운 노드 넣기
        size--; // 노드 수 감소

        // 나머지 노드를 앞으로 이동시키고 정렬
        for (int i = 1; i < size; i++) {
            nodes[i] = nodes[i + 1];
        }

        // 새 배열 정렬
        qsort(nodes, size, sizeof(Node*), compare);
    }

    Node* root = nodes[0]; // 루트 노드 반환
    free(nodes); // 메모리 해제
    return root;
}

// 코드 출력 함수
void printCodes(Node* root, int arr[], int top) {
    // 리프 노드인 경우 문자와 빈도수 출력
    if (root->left == NULL && root->right == NULL) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]); // 코드를 출력
        }
        printf("\n");
        return;
    }

    // 왼쪽 자식에 1 할당
    arr[top] = 1;
    printCodes(root->left, arr, top + 1); // 왼쪽 서브트리 호출

    // 오른쪽 자식에 0 할당
    arr[top] = 0;
    printCodes(root->right, arr, top + 1); // 오른쪽 서브트리 호출
}

// 주요 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int arr[size], top = 0;
    printCodes(root, arr, top);
}

// 메인 함수
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}
