#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MAX_EDGES 20

// Edge ����ü: �� ������ ������ ����ġ�� ����
typedef struct {
    int u, v, weight;
} Edge;

// GraphType ����ü: ������ ����, ������ ���� �� ���� �迭�� ����
typedef struct {
    int n; // ������ ����
    int ne; // ������ ����
    Edge edges[MAX_EDGES];
} GraphType;

// �׷��� �ʱ�ȭ �Լ�: ������ ���� ������ 0���� ����
void graph_init(GraphType* g) {
    g->n = 0;
    g->ne = 0;
}

// �׷��� ���� �Լ�: ������ ������ ���� �� ���� ������ �ʱ�ȭ
void GenerateGraph(GraphType* g) {
    g->n = 10; // ���� ���� ����
    g->edges[0] = (Edge){ 2 - 1, 5 - 1, 1 };  // ���� �߰� (���� ��ȣ�� 0���� �����ϵ��� ����)
    g->edges[1] = (Edge){ 3 - 1, 4 - 1, 2 };
    g->edges[2] = (Edge){ 1 - 1, 2 - 1, 3 };
    g->edges[3] = (Edge){ 2 - 1, 4 - 1, 4 };
    g->edges[4] = (Edge){ 3 - 1, 8 - 1, 5 };
    g->edges[5] = (Edge){ 3 - 1, 7 - 1, 6 };
    g->edges[6] = (Edge){ 2 - 1, 6 - 1, 7 };
    g->edges[7] = (Edge){ 9 - 1, 10 - 1, 10 };
    g->edges[8] = (Edge){ 8 - 1, 10 - 1, 15 };
    g->ne = 9; // ���� ���� ����
}

// Union-Find �˰����� find �Լ�: �ش� ������ ��Ʈ �θ� ��ȯ
int find(int parent[], int v) {
    if (parent[v] == v)
        return v;
    return parent[v] = find(parent, parent[v]);
}

// Union-Find �˰����� union_sets �Լ�: �� ������ ��ħ
void union_sets(int parent[], int rank[], int u, int v) {
    u = find(parent, u);
    v = find(parent, v);
    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        rank[u]++;
    }
}

// ������ ����ġ�� ���� �����ϱ� ���� �� �Լ� (qsort ���)
int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Quick ��� Kruskal �˰��� �Լ�: �ּ� ���� Ʈ���� ����
void QuickKruskal(GraphType* g) {
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES] = { 0 };

    // �ʱ�ȭ: �� ������ �ڱ� �ڽ��� �θ�� ����
    for (int i = 0; i < g->n; i++)
        parent[i] = i;

    // ������ ����ġ �������� �������� ����
    qsort(g->edges, g->ne, sizeof(Edge), compare);

    printf("Quick Based Kruskal\n");
    for (int i = 0; i < g->ne; i++) {
        int u = g->edges[i].u;
        int v = g->edges[i].v;
        int weight = g->edges[i].weight;

        // �� ������ ���� ���տ� ���� ���� ���, ���� ����
        if (find(parent, u) != find(parent, v)) {
            union_sets(parent, rank, u, v);
            printf("Edge (%d, %d) select %d\n", u + 1, v + 1, weight);  // 1�� ���� ���� ���� ��ȣ�� ���
        }
    }
}

// MinHeap ����ü: ������ �ּ� ���� ����
typedef struct {
    Edge heap[MAX_EDGES];
    int size;
} MinHeap;

// MinHeap �ʱ�ȭ �Լ�
void init_minheap(MinHeap* h) {
    h->size = 0;
}

// MinHeap�� ��Ҹ� �����ϴ� �Լ�
void insert_minheap(MinHeap* h, Edge e) {
    int i = ++(h->size);

    while (i != 1 && e.weight < h->heap[i / 2].weight) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = e;
}

// MinHeap���� �ּڰ��� �����ϰ� ��ȯ�ϴ� �Լ�
Edge delete_minheap(MinHeap* h) {
    int parent = 1, child = 2;
    Edge item = h->heap[1];
    Edge temp = h->heap[(h->size)--];

    while (child <= h->size) {
        if (child < h->size && h->heap[child].weight > h->heap[child + 1].weight)
            child++;
        if (temp.weight <= h->heap[child].weight)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// MinHeap ��� Kruskal �˰��� �Լ�: �ּ� ���� Ʈ���� ����
void MinHeapKruskal(GraphType* g) {
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES] = { 0 };
    MinHeap h;
    init_minheap(&h);

    // �ʱ�ȭ: �� ������ �ڱ� �ڽ��� �θ�� ����
    for (int i = 0; i < g->n; i++)
        parent[i] = i;

    // ��� ������ �ּ� ���� ����
    for (int i = 0; i < g->ne; i++)
        insert_minheap(&h, g->edges[i]);

    printf("MinHeap Based Kruskal\n");
    while (h.size > 0) {
        Edge e = delete_minheap(&h);
        int u = e.u;
        int v = e.v;
        int weight = e.weight;

        // �� ������ ���� ���տ� ���� ���� ���, ���� ����
        if (find(parent, u) != find(parent, v)) {
            union_sets(parent, rank, u, v);
            printf("Edge (%d, %d) select %d\n", u + 1, v + 1, weight);  // 1�� ���� ���� ���� ��ȣ�� ���
        }
    }
}

// main �Լ�: �׷��� �ʱ�ȭ, ���� �� Kruskal �˰��� ����
int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    if (g == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }
    graph_init(g); // �׷��� �ʱ�ȭ

    GenerateGraph(g); // �׷��� ����

    QuickKruskal(g); // Quick ��� Kruskal �˰��� ����
    MinHeapKruskal(g); // MinHeap ��� Kruskal �˰��� ����

    free(g); // �׷��� �޸� ����
    return 0;
}