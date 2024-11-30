//
// Created by 강민재 on 2024. 11. 24..
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Graph {
    struct Vertices* Vertices;
    struct Edge* Edge;
    int vertices_num;
    int edges_num;
} Graph;

typedef struct Vertices {
    int num;
    struct IncidenceList* incidenceList;
    int min_weight;
} Vertices;

typedef struct IncidenceList {
    int edge_idx;
    struct IncidenceList* next;
} IncidenceList;

typedef struct Edge {
    int v1_num;
    int v2_num;
    int weight;
} Edge;

Graph initGraph();
IncidenceList* getIncidence(int idx);
void addIncidenceNode(Graph G, int vertice_num, int edge_idx);
void insertEdge(Graph G, int v1, int v2, int weight);

void PrimJarnikMST(Graph G);
Vertices* removeMin(Vertices* Q[], int n);

int main() {
    Graph G = initGraph();
    PrimJarnikMST(G);

    return 0;
}

Graph initGraph() {
    Graph G;
    scanf("%d %d", &G.vertices_num, &G.edges_num);
    G.Vertices = (Vertices*)malloc(sizeof(Vertices) * G.vertices_num);
    G.Edge = (Edge*)malloc(sizeof(Edge) * G.edges_num);

    for (int i = 0; i < G.vertices_num; i++) {
        G.Vertices[i].num = i + 1;
        G.Vertices[i].incidenceList = getIncidence(-1);
    }

    for (int i = 0; i < G.edges_num; i++) {
        G.Edge[i].v1_num = G.Edge[i].v2_num = -1;

        int v1, v2, weight;
        scanf("%d %d %d", &v1, &v2, &weight);
        insertEdge(G, v1, v2, weight);
    }

    return G;
}

IncidenceList* getIncidence(int idx) {
    IncidenceList* newIncidenceList = (IncidenceList*)malloc(sizeof(IncidenceList));
    newIncidenceList->next = NULL;
    newIncidenceList->edge_idx = idx;

    return newIncidenceList;
}

void addIncidenceNode(Graph G, int vertice_num, int edge_idx) {
    IncidenceList* incidenceHead = G.Vertices[vertice_num - 1].incidenceList;
    IncidenceList* newIncidenceNode = getIncidence(edge_idx);

    newIncidenceNode->next = incidenceHead->next;
    incidenceHead->next = newIncidenceNode;

    return;
}

void insertEdge(Graph G, int v1, int v2, int weight) {
    if (v1 > v2) {
        int tmp = v1; v1 = v2; v2 = tmp;
    }

    int i = 0;
    while (G.Edge[i].v1_num != -1) i++;

    G.Edge[i].v1_num = v1 - 1;
    G.Edge[i].v2_num = v2 - 1;
    G.Edge[i].weight = weight;

    addIncidenceNode(G, v1, i);
    if (v1 != v2) addIncidenceNode(G, v2, i);

    return;
}

void PrimJarnikMST(Graph G) {
    int total_weight = 0;

    for (int i = 0; i < G.vertices_num; i++) {
        G.Vertices[i].min_weight = INT_MAX;
    }

    G.Vertices[0].min_weight = 0;

    Vertices* Q[G.vertices_num];
    for (int i = 0; i < G.vertices_num; i++) {
        Q[i] = &G.Vertices[i];
    }

    int n = G.vertices_num;
    while (n > 0) {
        Vertices* u = removeMin(Q, n);
        printf(" %d", u->num);
        total_weight += u->min_weight;
        n--;

        IncidenceList* uIncidenceList = u->incidenceList;
        while (uIncidenceList->next != NULL) {
            uIncidenceList = uIncidenceList->next;

            int zN = G.Edge[uIncidenceList->edge_idx].v2_num + 1;
            if (zN == u->num) {
                zN = G.Edge[uIncidenceList->edge_idx].v1_num + 1;
            }

            Vertices* oppose = &G.Vertices[zN - 1];
            if (G.Edge[uIncidenceList->edge_idx].weight < oppose->min_weight) {
                oppose->min_weight = G.Edge[uIncidenceList->edge_idx].weight;
            }
        }
    }

    printf("\n%d", total_weight);

    return;
}

Vertices* removeMin(Vertices* Q[], int n) {
    int m = INT_MAX;
    int idx = -1;
    for (int i = 0; i < n; i++) {
        if (Q[i]->min_weight < m) {
            m = Q[i]->min_weight;
            idx = i;
        }
    }

    Vertices* tmp = Q[n - 1];
    Q[n - 1] = Q[idx];
    Q[idx] = tmp;

    return Q[n - 1];
}