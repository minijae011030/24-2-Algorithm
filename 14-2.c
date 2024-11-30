//
// Created by 강민재 on 2024. 11. 30..
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Vertices {
    int distance;
    int in_degree;
    int out_degree;
} Vertices;

typedef struct Edge {
    int to_index;
    int from_index;
    int weight;
} Edge;

typedef struct Graph {
    struct Vertices* vertices;
    struct Edge* edge;
    int vertice_num;
    int edge_num;
    int start_index;
} Graph;

Graph initGraph();
void BellmanFord(Graph G, Vertices* start_vertice);

int main() {
    Graph G = initGraph();

    BellmanFord(G, &G.vertices[G.start_index]);

    if (G.vertices[G.start_index].out_degree != 0) {
        for (int i = 0; i < G.vertice_num; i++) {
            if (i != G.start_index && G.vertices[i].distance != 30000) {
                printf("%d %d\n", i + 1, G.vertices[i].distance);
            }
        }
    }

    return 0;
}

Graph initGraph() {
    Graph G;
    scanf("%d %d %d", &G.vertice_num, &G.edge_num, &G.start_index);
    G.start_index--;

    G.vertices = (Vertices*)malloc(sizeof(Vertices) * G.vertice_num);
    for (int i = 0; i < G.vertice_num; i++) {
        G.vertices[i].in_degree = 0;
        G.vertices[i].out_degree = 0;
    }

    G.edge = (Edge*)malloc(sizeof(Edge) * G.edge_num);
    for (int i = 0; i < G.edge_num; i++) {
        int from_index, to_index, weight;
        scanf("%d %d %d", &from_index, &to_index, &weight);

        G.vertices[to_index - 1].in_degree++;
        G.vertices[from_index - 1].out_degree++;
        G.edge[i].from_index = from_index - 1;
        G.edge[i].to_index = to_index - 1;
        G.edge[i].weight = weight;
    }

    return G;
}

void BellmanFord(Graph G, Vertices* start_vertice) {
    for (int i = 0; i < G.vertice_num; i++) {
        G.vertices[i].distance = 30000;
    }

    start_vertice->distance = 0;

    for (int i = 0; i < G.vertice_num - 1; i++) {
        for (int j = 0; j < G.edge_num; j++) {
            Vertices* u = &G.vertices[G.edge[j].from_index];
            Vertices* z = &G.vertices[G.edge[j].to_index];
            int weight = G.edge[j].weight;

            if (u->distance != 30000 && u->distance + weight < z->distance) {
                z->distance = u->distance + weight;
            }
        }
    }
}