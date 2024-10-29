#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10
#define MAX_EDGES 20

// Edge 구조체: 두 정점과 간선의 가중치를 포함
typedef struct {
    int u, v, weight;
} Edge;

// GraphType 구조체: 정점의 개수, 간선의 개수 및 간선 배열을 포함
typedef struct {
    int n; // 정점의 개수
    int ne; // 간선의 개수
    Edge edges[MAX_EDGES];
} GraphType;

// 그래프 초기화 함수: 정점과 간선 개수를 0으로 설정
void graph_init(GraphType* g) {
    g->n = 0;
    g->ne = 0;
}

// 그래프 생성 함수: 정점과 간선의 개수 및 간선 정보를 초기화
void GenerateGraph(GraphType* g) {
    g->n = 10; // 정점 개수 설정
    g->edges[0] = (Edge){ 2 - 1, 5 - 1, 1 };  // 간선 추가 (정점 번호는 0부터 시작하도록 조정)
    g->edges[1] = (Edge){ 3 - 1, 4 - 1, 2 };
    g->edges[2] = (Edge){ 1 - 1, 2 - 1, 3 };
    g->edges[3] = (Edge){ 2 - 1, 4 - 1, 4 };
    g->edges[4] = (Edge){ 3 - 1, 8 - 1, 5 };
    g->edges[5] = (Edge){ 3 - 1, 7 - 1, 6 };
    g->edges[6] = (Edge){ 2 - 1, 6 - 1, 7 };
    g->edges[7] = (Edge){ 9 - 1, 10 - 1, 10 };
    g->edges[8] = (Edge){ 8 - 1, 10 - 1, 15 };
    g->ne = 9; // 간선 개수 설정
}

// Union-Find 알고리즘의 find 함수: 해당 정점의 루트 부모를 반환
int find(int parent[], int v) {
    if (parent[v] == v)
        return v;
    return parent[v] = find(parent, parent[v]);
}

// Union-Find 알고리즘의 union_sets 함수: 두 집합을 합침
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

// 간선을 가중치에 따라 정렬하기 위한 비교 함수 (qsort 사용)
int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

// Quick 기반 Kruskal 알고리즘 함수: 최소 신장 트리를 생성
void QuickKruskal(GraphType* g) {
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES] = { 0 };

    // 초기화: 각 정점을 자기 자신을 부모로 설정
    for (int i = 0; i < g->n; i++)
        parent[i] = i;

    // 간선을 가중치 기준으로 오름차순 정렬
    qsort(g->edges, g->ne, sizeof(Edge), compare);

    printf("Quick Based Kruskal\n");
    for (int i = 0; i < g->ne; i++) {
        int u = g->edges[i].u;
        int v = g->edges[i].v;
        int weight = g->edges[i].weight;

        // 두 정점이 같은 집합에 있지 않은 경우, 간선 선택
        if (find(parent, u) != find(parent, v)) {
            union_sets(parent, rank, u, v);
            printf("Edge (%d, %d) select %d\n", u + 1, v + 1, weight);  // 1을 더해 원래 정점 번호로 출력
        }
    }
}

// MinHeap 구조체: 간선의 최소 힙을 저장
typedef struct {
    Edge heap[MAX_EDGES];
    int size;
} MinHeap;

// MinHeap 초기화 함수
void init_minheap(MinHeap* h) {
    h->size = 0;
}

// MinHeap에 요소를 삽입하는 함수
void insert_minheap(MinHeap* h, Edge e) {
    int i = ++(h->size);

    while (i != 1 && e.weight < h->heap[i / 2].weight) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = e;
}

// MinHeap에서 최솟값을 삭제하고 반환하는 함수
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

// MinHeap 기반 Kruskal 알고리즘 함수: 최소 신장 트리를 생성
void MinHeapKruskal(GraphType* g) {
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES] = { 0 };
    MinHeap h;
    init_minheap(&h);

    // 초기화: 각 정점을 자기 자신을 부모로 설정
    for (int i = 0; i < g->n; i++)
        parent[i] = i;

    // 모든 간선을 최소 힙에 삽입
    for (int i = 0; i < g->ne; i++)
        insert_minheap(&h, g->edges[i]);

    printf("MinHeap Based Kruskal\n");
    while (h.size > 0) {
        Edge e = delete_minheap(&h);
        int u = e.u;
        int v = e.v;
        int weight = e.weight;

        // 두 정점이 같은 집합에 있지 않은 경우, 간선 선택
        if (find(parent, u) != find(parent, v)) {
            union_sets(parent, rank, u, v);
            printf("Edge (%d, %d) select %d\n", u + 1, v + 1, weight);  // 1을 더해 원래 정점 번호로 출력
        }
    }
}

// main 함수: 그래프 초기화, 생성 및 Kruskal 알고리즘 수행
int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    if (g == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }
    graph_init(g); // 그래프 초기화

    GenerateGraph(g); // 그래프 생성

    QuickKruskal(g); // Quick 기반 Kruskal 알고리즘 실행
    MinHeapKruskal(g); // MinHeap 기반 Kruskal 알고리즘 실행

    free(g); // 그래프 메모리 해제
    return 0;
}