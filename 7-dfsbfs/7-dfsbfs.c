#include <stdio.h>
#include <stdlib.h>

#define MAX 11  // �ִ� ��� ����

// �׷��� ����ü
typedef struct {
    int adj[MAX][MAX];  // ���� ��ķ� �׷��� ǥ��
    int visited[MAX];   // �湮 ���θ� �����ϴ� �迭
} Graph;

// ���ð� ť ����ü ����
typedef struct {
    int items[MAX];
    int top;
} Stack;

typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

// ���� ���� �Լ�
void initStack(Stack* s) {
    s->top = -1;
}

int isStackEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    s->items[++(s->top)] = value;
}

int pop(Stack* s) {
    return s->items[(s->top)--];
}

// ť ���� �Լ�
void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

int isQueueEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++(q->rear)] = value;
}

int dequeue(Queue* q) {
    int value = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    }
    else {
        q->front++;
    }
    return value;
}

// ���� �켱 Ž��(DFS)
void DFS(Graph* g, int start, int target) {
    Stack stack;
    initStack(&stack);
    push(&stack, start);

    int found = 0;
    int visitedCount = 0;

    // �湮 �迭 �ʱ�ȭ
    for (int i = 0; i < MAX; i++) {
        g->visited[i] = 0;
    }

    while (!isStackEmpty(&stack)) {
        int current = pop(&stack);

        if (!g->visited[current]) {
            g->visited[current] = 1;
            printf("%d ", current);
            visitedCount++;

            if (current == target) {
                found = 1;
                break;
            }

            for (int i = MAX - 1; i >= 0; i--) {
                if (g->adj[current][i] && !g->visited[i]) {
                    push(&stack, i);
                }
            }
        }
    }

    if (found) {
        printf("\nŽ�� ����: %d\n", target);
    }
    else {
        printf("\nŽ�� ����: %d\n", target);
    }
    printf("�湮�� ����� ��: %d\n", visitedCount);
}

// �ʺ� �켱 Ž��(BFS)
void BFS(Graph* g, int start, int target) {
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, start);

    int found = 0;
    int visitedCount = 0;

    // �湮 �迭 �ʱ�ȭ
    for (int i = 0; i < MAX; i++) {
        g->visited[i] = 0;
    }

    while (!isQueueEmpty(&queue)) {
        int current = dequeue(&queue);

        if (!g->visited[current]) {
            g->visited[current] = 1;
            printf("%d ", current);
            visitedCount++;

            if (current == target) {
                found = 1;
                break;
            }

            for (int i = 0; i < MAX; i++) {
                if (g->adj[current][i] && !g->visited[i]) {
                    enqueue(&queue, i);
                }
            }
        }
    }

    if (found) {
        printf("\nŽ�� ����: %d\n", target);
    }
    else {
        printf("\nŽ�� ����: %d\n", target);
    }
    printf("�湮�� ����� ��: %d\n", visitedCount);
}

// �׷��� �ʱ�ȭ �Լ�
void initGraph(Graph* g) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            g->adj[i][j] = 0;
        }
        g->visited[i] = 0;
    }
}

int main() {
    Graph g;
    initGraph(&g);

    //�׷��� ���� ��ķ� ����
    g.adj[0][2] = g.adj[0][6] = g.adj[0][1] = 1;  // 0�� ��尡 1�� ���� �����
    g.adj[1][0] = 1;  // 1�� ���� 0�� ��带 ��������� ����
    g.adj[2][0] = g.adj[2][3] = g.adj[2][5] = 1;
    g.adj[3][2] = g.adj[3][5] = 1;
    g.adj[4][5] = g.adj[4][6] = g.adj[4][7] = 1;
    g.adj[5][2] = g.adj[5][3] = g.adj[5][4] = 1;
    g.adj[6][0] = g.adj[6][4] = g.adj[6][8] = g.adj[6][9] = 1;
    g.adj[7][4] = g.adj[7][8] = g.adj[7][10] = 1;
    g.adj[8][6] = g.adj[8][7] = g.adj[8][9] = 1;
    g.adj[9][6] = g.adj[9][8] = 1;
    g.adj[10][7] = 1;

    // ��� 9�� ���� ���� (��: ��� 8�� ����)
    g.adj[8][9] = 1;  // 8�� ���� 9�� ��带 ����
    g.adj[9][8] = 1;  // 9�� ���� 8�� ��带 ��������� ����

    int menu, start, target;

    while (1) {
        printf("1 : ���� �켱 Ž��\n");
        printf("2 : �ʺ� �켱 Ž��\n");
        printf("3 : ����\n");
        printf("�޴� �Է�: ");
        if (scanf("%d", &menu) != 1) {
            printf("�߸��� �Է��Դϴ�.\n");
            while (getchar() != '\n');
            continue;
        }

        if (menu == 3) break;

        printf("���� ��ȣ�� Ž���� �� �Է�: ");
        if (scanf("%d %d", &start, &target) != 2) {
            printf("�߸��� �Է��Դϴ�.\n");
            while (getchar() != '\n');
            continue;
        }

        if (start < 0 || start >= MAX || target < 0 || target >= MAX) {
            printf("�߸��� �Է��Դϴ�.\n");
            continue;
        }

        switch (menu) {
        case 1:
            DFS(&g, start, target);
            break;
        case 2:
            BFS(&g, start, target);
            break;
        default:
            printf("�߸��� �޴� �����Դϴ�.\n");
        }
        printf("\n");
    }

    return 0;
}
