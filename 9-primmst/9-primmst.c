#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
    int n;  // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES]; // 인접 행렬
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = 0;  // 정점 개수 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = (i == j) ? 0 : INF;  // 자기 자신과의 거리는 0, 나머지는 무한대
        }
    }
}

// 엣지를 추가하는 함수
void insert_edge(GraphType* g, int u, int v, int w) {
    g->weight[u - 1][v - 1] = w;  // 인덱스를 0부터 시작하도록 조정
    g->weight[v - 1][u - 1] = w;  // 무향 그래프이므로 대칭으로 설정
}

// 그래프 생성 함수
void GenerateGraph(GraphType* g) {
    g->n = 10;  // 정점 수 설정

    // 엣지를 추가하여 가중치 행렬 설정
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 3, 7);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

// Prim 알고리즘을 이용한 MST 찾기
void FindPrimMST(GraphType* g) {
    int u, v;
    int totalWeight = 0;

    // 시작 정점 설정 (정점 1 선택)
    selected[0] = TRUE;  // 정점 1을 선택
    for (int i = 1; i < g->n; i++) {
        selected[i] = FALSE;  // 나머지 정점 초기화
        distance[i] = g->weight[0][i];  // 정점 1과의 거리 초기화
    }

    printf("Prim MST Algorithm\n");
    printf("정점 1 추가\n");  // 첫 번째 정점 추가 출력

    for (int i = 1; i < g->n; i++) {
        int min = INF;
        u = 0;

        // 가장 가까운 정점 찾기
        for (v = 1; v < g->n; v++) {
            if (!selected[v] && distance[v] < min) {
                min = distance[v];
                u = v;
            }
        }

        // 선택한 정점 추가
        selected[u] = TRUE;
        totalWeight += distance[u];
        printf("정점 %d 추가\n", u + 1);  // 정점 번호는 1부터 시작

        // 인접한 정점 거리 업데이트
        for (v = 0; v < g->n; v++) {
            if (!selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];
            }
        }
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    // 그래프를 생성하는 함수
    GenerateGraph(g);

    FindPrimMST(g);  // Prim을 이용해 MST를 찾음

    free(g);
    return 0;
}
