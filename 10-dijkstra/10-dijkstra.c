#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

typedef struct {
    int n;  // 정점의 수
    int weight[MAX_VERTICES][MAX_VERTICES];  // 인접 행렬로 그래프의 가중치 저장
} Graph;

int distance[MAX_VERTICES];  // 시작 정점으로부터의 최단 거리
int visited[MAX_VERTICES];   // 방문 여부를 나타내는 배열
int visitOrder[MAX_VERTICES]; // 방문 순서를 저장하는 배열
int visitIndex = 0;           // 방문 순서를 위한 인덱스

// 그래프 초기화 함수
void initGraph(Graph* g, int vertices) {
    g->n = vertices;
    for (int i = 1; i <= vertices; i++) {
        for (int j = 1; j <= vertices; j++) {
            if (i == j)
                g->weight[i][j] = 0;  // 자기 자신으로의 거리는 0
            else
                g->weight[i][j] = INF; // 초기화 시 연결이 없는 경우 INF로 설정
        }
    }
}

// 그래프에 간선 추가 함수
void addEdge(Graph* g, int u, int v, int weight) {
    g->weight[u][v] = weight;
    g->weight[v][u] = weight;  // 양방향 그래프이므로 대칭적으로 설정
}

// 방문하지 않은 정점 중 가장 짧은 거리를 가진 정점을 찾는 함수
int selectMinVertex(int n) {
    int minVertex = -1;
    int minDistance = INF;

    for (int i = 1; i <= n; i++) {
        if (!visited[i] && distance[i] < minDistance) {
            minVertex = i;
            minDistance = distance[i];
        }
    }
    return minVertex;
}

// 현재 상태 출력 함수
void printCurrentStatus(int vertices) {
    printf("Distance: ");
    for (int i = 1; i <= vertices; i++) {
        if (distance[i] == INF)
            printf("* ");
        else
            printf("%d ", distance[i]);
    }
    printf("\nVisited:  ");
    for (int i = 1; i <= vertices; i++) {
        printf("%d ", visited[i]);
    }
    printf("\n\n");
}

// Dijkstra 알고리즘 함수
void dijkstra(Graph* g, int startVertex) {
    // 초기화
    for (int i = 1; i <= g->n; i++) {
        distance[i] = INF;
        visited[i] = 0;
    }
    distance[startVertex] = 0;  // 시작 정점의 거리를 0으로 설정

    // 정점의 개수만큼 반복
    for (int i = 0; i < g->n; i++) {
        int u = selectMinVertex(g->n); // 최소 거리 정점 선택
        if (u == -1) break; // 더 이상 선택할 정점이 없으면 종료

        visited[u] = 1;  // 선택된 정점을 방문 처리
        visitOrder[visitIndex++] = u;  // 방문 순서에 기록

        // 현재 상태 출력
        printCurrentStatus(g->n);

        // 선택된 정점에 인접한 정점들의 거리 갱신
        for (int v = 1; v <= g->n; v++) {
            if (g->weight[u][v] != INF && !visited[v]) { // 연결되어 있고, 방문하지 않은 경우
                int newDistance = distance[u] + g->weight[u][v];
                if (newDistance < distance[v]) {
                    distance[v] = newDistance;  // 더 짧은 거리로 갱신
                }
            }
        }
    }

    // 방문 순서 출력
    printf("Visit Order: ");
    for (int i = 0; i < visitIndex; i++) {
        printf("%d ", visitOrder[i]);
    }
    printf("\n");
}

// 그래프 생성 함수
void createSampleGraph(Graph* g) {
    addEdge(g, 1, 2, 3);
    addEdge(g, 1, 6, 11);
    addEdge(g, 1, 7, 12);
    addEdge(g, 2, 6, 7);
    addEdge(g, 2, 3, 5);
    addEdge(g, 2, 4, 4);
    addEdge(g, 2, 5, 1);
    addEdge(g, 2, 7, 8);
    addEdge(g, 3, 8, 5);
    addEdge(g, 3, 7, 6);
    addEdge(g, 3, 4, 2);
    addEdge(g, 4, 5, 13);
    addEdge(g, 4, 10, 16);
    addEdge(g, 4, 8, 14);
    addEdge(g, 5, 10, 17);
    addEdge(g, 5, 6, 9);
    addEdge(g, 5, 9, 18);
    addEdge(g, 8, 10, 15);
    addEdge(g, 9, 10, 10);
}

// 메인 함수
int main() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    initGraph(g, 10);  // 정점 개수를 10으로 초기화

    createSampleGraph(g);  // 그래프에 간선 추가

    dijkstra(g, 1);  // 정점 1을 시작으로 Dijkstra 알고리즘 실행

    free(g);
    return 0;
}
