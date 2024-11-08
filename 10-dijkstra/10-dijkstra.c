#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

typedef struct {
    int n;  // ������ ��
    int weight[MAX_VERTICES][MAX_VERTICES];  // ���� ��ķ� �׷����� ����ġ ����
} Graph;

int distance[MAX_VERTICES];  // ���� �������κ����� �ִ� �Ÿ�
int visited[MAX_VERTICES];   // �湮 ���θ� ��Ÿ���� �迭
int visitOrder[MAX_VERTICES]; // �湮 ������ �����ϴ� �迭
int visitIndex = 0;           // �湮 ������ ���� �ε���

// �׷��� �ʱ�ȭ �Լ�
void initGraph(Graph* g, int vertices) {
    g->n = vertices;
    for (int i = 1; i <= vertices; i++) {
        for (int j = 1; j <= vertices; j++) {
            if (i == j)
                g->weight[i][j] = 0;  // �ڱ� �ڽ������� �Ÿ��� 0
            else
                g->weight[i][j] = INF; // �ʱ�ȭ �� ������ ���� ��� INF�� ����
        }
    }
}

// �׷����� ���� �߰� �Լ�
void addEdge(Graph* g, int u, int v, int weight) {
    g->weight[u][v] = weight;
    g->weight[v][u] = weight;  // ����� �׷����̹Ƿ� ��Ī������ ����
}

// �湮���� ���� ���� �� ���� ª�� �Ÿ��� ���� ������ ã�� �Լ�
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

// ���� ���� ��� �Լ�
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

// Dijkstra �˰��� �Լ�
void dijkstra(Graph* g, int startVertex) {
    // �ʱ�ȭ
    for (int i = 1; i <= g->n; i++) {
        distance[i] = INF;
        visited[i] = 0;
    }
    distance[startVertex] = 0;  // ���� ������ �Ÿ��� 0���� ����

    // ������ ������ŭ �ݺ�
    for (int i = 0; i < g->n; i++) {
        int u = selectMinVertex(g->n); // �ּ� �Ÿ� ���� ����
        if (u == -1) break; // �� �̻� ������ ������ ������ ����

        visited[u] = 1;  // ���õ� ������ �湮 ó��
        visitOrder[visitIndex++] = u;  // �湮 ������ ���

        // ���� ���� ���
        printCurrentStatus(g->n);

        // ���õ� ������ ������ �������� �Ÿ� ����
        for (int v = 1; v <= g->n; v++) {
            if (g->weight[u][v] != INF && !visited[v]) { // ����Ǿ� �ְ�, �湮���� ���� ���
                int newDistance = distance[u] + g->weight[u][v];
                if (newDistance < distance[v]) {
                    distance[v] = newDistance;  // �� ª�� �Ÿ��� ����
                }
            }
        }
    }

    // �湮 ���� ���
    printf("Visit Order: ");
    for (int i = 0; i < visitIndex; i++) {
        printf("%d ", visitOrder[i]);
    }
    printf("\n");
}

// �׷��� ���� �Լ�
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

// ���� �Լ�
int main() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    initGraph(g, 10);  // ���� ������ 10���� �ʱ�ȭ

    createSampleGraph(g);  // �׷����� ���� �߰�

    dijkstra(g, 1);  // ���� 1�� �������� Dijkstra �˰��� ����

    free(g);
    return 0;
}
