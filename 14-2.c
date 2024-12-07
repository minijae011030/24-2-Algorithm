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

    // 시작 정점에서 다른 정점들까지의 거리 출력
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

// 벨먼-포드 알고리즘
void BellmanFord(Graph G, Vertices* start_vertice) {
    // 모든 정점의 초기 거리 설정
    for (int i = 0; i < G.vertice_num; i++) {
        G.vertices[i].distance = 30000; // 초기 거리를 매우 큰 값으로 설정
    }

    // 시작 정점의 거리 0으로 설정
    start_vertice->distance = 0;

    // 정점 개수 - 1 만큼 반복
    // 각 정점에서 간선을 통해 최단 거리를 반복적으로 업데이트
    for (int i = 0; i < G.vertice_num - 1; i++) {
        for (int j = 0; j < G.edge_num; j++) {
            Vertices* u = &G.vertices[G.edge[j].from_index]; // 간선의 시작 정점
            Vertices* z = &G.vertices[G.edge[j].to_index];   // 간선의 도착 정점
            int weight = G.edge[j].weight;                  // 간선 가중치

            // 시작 정점으로부터의 거리가 유효하고, 현재 계산된 거리보다 작다면 업데이트
            if (u->distance != 30000 && u->distance + weight < z->distance) {
                z->distance = u->distance + weight; // 거리 갱신
            }
        }
    }
}