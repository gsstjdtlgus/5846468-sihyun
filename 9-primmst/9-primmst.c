#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
    int n;  // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES]; // ���� ���
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// �׷��� �ʱ�ȭ �Լ�
void graph_init(GraphType* g) {
    g->n = 0;  // ���� ���� �ʱ�ȭ
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = (i == j) ? 0 : INF;  // �ڱ� �ڽŰ��� �Ÿ��� 0, �������� ���Ѵ�
        }
    }
}

// ������ �߰��ϴ� �Լ�
void insert_edge(GraphType* g, int u, int v, int w) {
    g->weight[u - 1][v - 1] = w;  // �ε����� 0���� �����ϵ��� ����
    g->weight[v - 1][u - 1] = w;  // ���� �׷����̹Ƿ� ��Ī���� ����
}

// �׷��� ���� �Լ�
void GenerateGraph(GraphType* g) {
    g->n = 10;  // ���� �� ����

    // ������ �߰��Ͽ� ����ġ ��� ����
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

// Prim �˰����� �̿��� MST ã��
void FindPrimMST(GraphType* g) {
    int u, v;
    int totalWeight = 0;

    // ���� ���� ���� (���� 1 ����)
    selected[0] = TRUE;  // ���� 1�� ����
    for (int i = 1; i < g->n; i++) {
        selected[i] = FALSE;  // ������ ���� �ʱ�ȭ
        distance[i] = g->weight[0][i];  // ���� 1���� �Ÿ� �ʱ�ȭ
    }

    printf("Prim MST Algorithm\n");
    printf("���� 1 �߰�\n");  // ù ��° ���� �߰� ���

    for (int i = 1; i < g->n; i++) {
        int min = INF;
        u = 0;

        // ���� ����� ���� ã��
        for (v = 1; v < g->n; v++) {
            if (!selected[v] && distance[v] < min) {
                min = distance[v];
                u = v;
            }
        }

        // ������ ���� �߰�
        selected[u] = TRUE;
        totalWeight += distance[u];
        printf("���� %d �߰�\n", u + 1);  // ���� ��ȣ�� 1���� ����

        // ������ ���� �Ÿ� ������Ʈ
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

    // �׷����� �����ϴ� �Լ�
    GenerateGraph(g);

    FindPrimMST(g);  // Prim�� �̿��� MST�� ã��

    free(g);
    return 0;
}
