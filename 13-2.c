//
// Created by 강민재 on 2024. 11. 24..
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Vertices {
    struct Vertices* parent;
    int rank;
} Vertices;

typedef struct Edge {
    int v1_idx;
    int v2_idx;
    int weight;
} Edge;

typedef struct Graph {
    struct Vertices* Vertices;
    struct Edge* Edge;
    int vertices_num;
    int edges_num;
} Graph;

typedef struct Kruskal {
    struct Edge* KruskalHeap;
    int total_weight;
    int idx;
} Kruskal;

Graph initGraph();

Kruskal* KruskalAlg(Graph* G);
Edge* removeMin(Edge** Q, int n);
Vertices* find(Graph G, Vertices* x);
void unionSet(Graph* G, Vertices* x, Vertices* y);

int main() {
    Graph G = initGraph();
    Kruskal* kruskal = KruskalAlg(&G);

    for (int i = 0; i < kruskal->idx; i++) {
        printf(" %d", kruskal->KruskalHeap[i].weight);
    }

    printf("\n%d", kruskal->total_weight);

    return 0;
}

Graph initGraph() {
    Graph G;
    scanf("%d %d", &G.vertices_num, &G.edges_num);

    G.Vertices = (Vertices*)malloc(sizeof(Vertices) * G.vertices_num);
    G.Edge = (Edge*)malloc(sizeof(Edge) * G.edges_num);

    for (int i = 0; i < G.vertices_num; i++) {
        G.Vertices[i].parent = &G.Vertices[i];
        G.Vertices[i].rank = 0;
    }

    for (int i = 0; i < G.edges_num; i++) {
        scanf("%d %d %d", &G.Edge[i].v1_idx, &G.Edge[i].v2_idx, &G.Edge[i].weight);

        G.Edge[i].v1_idx--;
        G.Edge[i].v2_idx--;
    }

    return G;
}

Kruskal* KruskalAlg(Graph* G) {
    int totalWeight = 0;

    Edge** Q = (Edge**)malloc(sizeof(Edge*) * G->edges_num);
    Edge* KruskalHeap = (Edge*)malloc(sizeof(Edge) * (G->vertices_num - 1));

    for (int i = 0; i < G->edges_num; i++)
        Q[i] = &G->Edge[i];

    int n = G->edges_num;
    int idx = 0;
    while (idx < G->vertices_num - 1) {
        Edge* minEdge = removeMin(Q, n);
        n--;

        Vertices* v1 = &G->Vertices[minEdge->v1_idx];
        Vertices* v2 = &G->Vertices[minEdge->v2_idx];

        Vertices* v1Parent = find(*G, v1);
        Vertices* v2Parent = find(*G, v2);

        if (v1Parent != v2Parent) {
            KruskalHeap[idx].v1_idx = minEdge->v1_idx;
            KruskalHeap[idx].v2_idx = minEdge->v2_idx;
            KruskalHeap[idx].weight = minEdge->weight;

            totalWeight += minEdge->weight;

            unionSet(G, v1, v2);

            idx++;
        }
    }

    Kruskal* kruskal = (Kruskal*)malloc(sizeof(Kruskal));;
    kruskal->KruskalHeap = KruskalHeap;
    kruskal->total_weight = totalWeight;
    kruskal->idx = idx;

    return kruskal;
}

Edge* removeMin(Edge** Q, int n) {
    int m = 10000;
    int idx = -1;

    for (int i = 0; i < n; i++) {
        if ((*Q[i]).weight < m) {
            idx = i;
            m = (*Q[i]).weight;
        }
    }

    Edge* tmp = Q[n - 1];
    Q[n - 1] = Q[idx];
    Q[idx] = tmp;

    return Q[n - 1];
}

Vertices* find(Graph G, Vertices* x) {
    if (x->parent != x) x->parent = find(G, x->parent);

    return x->parent;
}

void unionSet(Graph* G, Vertices* x, Vertices* y) {
    Vertices* rootX = find(*G, x);
    Vertices* rootY = find(*G, y);

    if (rootX != rootY) {
        if (rootX->rank < rootY->rank) rootX->parent = rootY;
        else if (rootX->rank > rootY->rank) rootY->parent = rootX;
        else {
            rootY->parent = rootX;
            rootX->rank++;
        }
    }
}