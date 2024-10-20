#include <stdio.h>
#include <stdlib.h>

#define MAX 11  // 최대 노드 개수

// 그래프 구조체
typedef struct {
    int adj[MAX][MAX];  // 인접 행렬로 그래프 표현
    int visited[MAX];   // 방문 여부를 저장하는 배열
} Graph;

// 스택과 큐 구조체 정의
typedef struct {
    int items[MAX];
    int top;
} Stack;

typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

// 스택 관련 함수
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

// 큐 관련 함수
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

// 깊이 우선 탐색(DFS)
void DFS(Graph* g, int start, int target) {
    Stack stack;
    initStack(&stack);
    push(&stack, start);

    int found = 0;
    int visitedCount = 0;

    // 방문 배열 초기화
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
        printf("\n탐색 성공: %d\n", target);
    }
    else {
        printf("\n탐색 실패: %d\n", target);
    }
    printf("방문한 노드의 수: %d\n", visitedCount);
}

// 너비 우선 탐색(BFS)
void BFS(Graph* g, int start, int target) {
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, start);

    int found = 0;
    int visitedCount = 0;

    // 방문 배열 초기화
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
        printf("\n탐색 성공: %d\n", target);
    }
    else {
        printf("\n탐색 실패: %d\n", target);
    }
    printf("방문한 노드의 수: %d\n", visitedCount);
}

// 그래프 초기화 함수
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

    //그래프 인접 행렬로 설정
    g.adj[0][2] = g.adj[0][6] = g.adj[0][1] = 1;  // 0번 노드가 1번 노드와 연결됨
    g.adj[1][0] = 1;  // 1번 노드와 0번 노드를 양방향으로 연결
    g.adj[2][0] = g.adj[2][3] = g.adj[2][5] = 1;
    g.adj[3][2] = g.adj[3][5] = 1;
    g.adj[4][5] = g.adj[4][6] = g.adj[4][7] = 1;
    g.adj[5][2] = g.adj[5][3] = g.adj[5][4] = 1;
    g.adj[6][0] = g.adj[6][4] = g.adj[6][8] = g.adj[6][9] = 1;
    g.adj[7][4] = g.adj[7][8] = g.adj[7][10] = 1;
    g.adj[8][6] = g.adj[8][7] = g.adj[8][9] = 1;
    g.adj[9][6] = g.adj[9][8] = 1;
    g.adj[10][7] = 1;

    // 노드 9와 연결 설정 (예: 노드 8과 연결)
    g.adj[8][9] = 1;  // 8번 노드와 9번 노드를 연결
    g.adj[9][8] = 1;  // 9번 노드와 8번 노드를 양방향으로 연결

    int menu, start, target;

    while (1) {
        printf("1 : 깊이 우선 탐색\n");
        printf("2 : 너비 우선 탐색\n");
        printf("3 : 종료\n");
        printf("메뉴 입력: ");
        if (scanf("%d", &menu) != 1) {
            printf("잘못된 입력입니다.\n");
            while (getchar() != '\n');
            continue;
        }

        if (menu == 3) break;

        printf("시작 번호와 탐색할 값 입력: ");
        if (scanf("%d %d", &start, &target) != 2) {
            printf("잘못된 입력입니다.\n");
            while (getchar() != '\n');
            continue;
        }

        if (start < 0 || start >= MAX || target < 0 || target >= MAX) {
            printf("잘못된 입력입니다.\n");
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
            printf("잘못된 메뉴 선택입니다.\n");
        }
        printf("\n");
    }

    return 0;
}
