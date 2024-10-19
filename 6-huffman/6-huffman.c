#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char character;
    int frequency;
    struct Node* left;
    struct Node* right;
} Node;

// �켱���� ť�� ��带 ���� �� �Լ�
int compare(const void* a, const void* b) {
    return ((Node*)a)->frequency - ((Node*)b)->frequency;
}

// ��� ���� �Լ�
Node* createNode(char character, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Huffman Ʈ���� �����ϴ� �Լ�
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    Node** nodes = (Node**)malloc(size * sizeof(Node*));

    // ��� �迭 �ʱ�ȭ
    for (int i = 0; i < size; i++) {
        nodes[i] = createNode(characters[i], frequencies[i]);
    }

    // �켱���� ť�� ����Ͽ� �ּ� ���� ����
    qsort(nodes, size, sizeof(Node*), compare);

    // Ʈ�� ����
    while (size > 1) {
        // �� ���� ���� ���� ��� ����
        Node* left = nodes[0];
        Node* right = nodes[1];

        // ���ο� ��� ����
        Node* newNode = createNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        // �� ��带 �迭�� �߰��ϰ� ����
        nodes[1] = newNode; // �� ��° �ڸ��� ���ο� ��� �ֱ�
        size--; // ��� �� ����

        // ������ ��带 ������ �̵���Ű�� ����
        for (int i = 1; i < size; i++) {
            nodes[i] = nodes[i + 1];
        }

        // �� �迭 ����
        qsort(nodes, size, sizeof(Node*), compare);
    }

    Node* root = nodes[0]; // ��Ʈ ��� ��ȯ
    free(nodes); // �޸� ����
    return root;
}

// �ڵ� ��� �Լ�
void printCodes(Node* root, int arr[], int top) {
    // ���� ����� ��� ���ڿ� �󵵼� ���
    if (root->left == NULL && root->right == NULL) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]); // �ڵ带 ���
        }
        printf("\n");
        return;
    }

    // ���� �ڽĿ� 1 �Ҵ�
    arr[top] = 1;
    printCodes(root->left, arr, top + 1); // ���� ����Ʈ�� ȣ��

    // ������ �ڽĿ� 0 �Ҵ�
    arr[top] = 0;
    printCodes(root->right, arr, top + 1); // ������ ����Ʈ�� ȣ��
}

// �ֿ� �Լ�
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int arr[size], top = 0;
    printCodes(root, arr, top);
}

// ���� �Լ�
int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}
