//
// Created by 강민재 on 2024. 11. 30..
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    struct Vertices* Vertices;
    struct Edge* Edge;
    int vertice_num;
    int edge_num;
    int start_index;
} Graph;

typedef struct Vertices {
    int num;
    struct IncidenceList* incidenceList;
    int distance;
} Vertices;

typedef struct Edge {
    int v1_index;
    int v2_index;
    int weight;
} Edge;

typedef struct IncidenceList {
    struct IncidenceList* next;
    int edge_index;
} IncidenceList;

Graph initGraph();
IncidenceList* getIncidenceList(int index);
void addIncidenceNode(Graph G, int vertice_num, int edge_index);
void insertEdge(Graph G, int i, int v1, int v2, int weight);

void Dijkstra(Graph G);
Vertices* removeMin(Vertices** Q, int n);

int main() {
    Graph G = initGraph();
    Dijkstra(G);

    // 시작 정점을 제외한 각 정점의 최단 거리 출력
    for (int i = 0; i < G.vertice_num; i++) {
        if (i != G.start_index && G.Vertices[i].distance != 30000) {
            printf("%d %d\n", i + 1, G.Vertices[i].distance);
        }
    }

    return 0;
}

Graph initGraph() {
    Graph G;
    scanf("%d %d %d", &G.vertice_num, &G.edge_num, &G.start_index);
    G.start_index--;
    G.Vertices = (Vertices*)malloc(sizeof(Vertices) * G.vertice_num);
    G.Edge = (Edge*)malloc(sizeof(Edge) * G.edge_num);

    for (int i = 0; i < G.vertice_num; i++) {
        G.Vertices[i].num = i + 1;
        G.Vertices[i].incidenceList = getIncidenceList(-1);
    }

    for (int i = 0; i < G.edge_num; i++) {
        int v1, v2, weight;
        scanf("%d %d %d", &v1, &v2, &weight);
        insertEdge(G, i, v1, v2, weight);
    }

    return G;
}

IncidenceList* getIncidenceList(int index) {
    IncidenceList* newIncidenceNode = (IncidenceList*)malloc(sizeof(IncidenceList));
    newIncidenceNode->next = NULL;
    newIncidenceNode->edge_index = index;

    return newIncidenceNode;
}

void addIncidenceNode(Graph G, int vertice_num, int edge_index) {
    IncidenceList* incidenceHead = G.Vertices[vertice_num - 1].incidenceList;

    IncidenceList* newIncidenceNode = getIncidenceList(edge_index);
    newIncidenceNode->next = incidenceHead->next;
    incidenceHead->next = newIncidenceNode;
}

void insertEdge(Graph G, int i, int v1, int v2, int weight) {
   if (v1 > v2) {
       int tmp = v1;
       v1 = v2;
       v2 = tmp;
   }

   G.Edge[i].v1_index = v1 - 1;
   G.Edge[i].v2_index = v2 - 1;
   G.Edge[i].weight = weight;

   addIncidenceNode(G, v1, i);
   if (v1 != v2) addIncidenceNode(G, v2, i);
}

// 다익스트라 알고리즘
void Dijkstra(Graph G) {
    // 간선 리스트가 비어 있지 않은 정점의 수 계산
    int n = 0;
    for (int i = 0; i < G.vertice_num; i++) {
        if (G.Vertices[i].incidenceList->next != NULL) {
            n++;    // 간선 리스트가 비어있지 않은 정점의 개수 카운트
        }
    }

    // 우선순위 큐 초기화
    Vertices** Q = (Vertices**)malloc(sizeof(Vertices*) * n);

    // 정점 거리 초기화
    int idx = 0;
    for (int i = 0; i < G.vertice_num; i++) {
        G.Vertices[i].distance = 30000; // 초기 거리를 매우 큰 값으로 설정
        if (G.Vertices[i].incidenceList->next != NULL) {
            Q[idx] = &G.Vertices[i];    // 큐에 정점 추가
            idx++;
        }
    }

    // 시작 정점의 거리 초기화
    G.Vertices[G.start_index].distance = 0;

    // 다익스트라 메인 루프
    while (n > 0) {
        Vertices* u = removeMin(Q, n--); // 최소 거리 정점 추출
        IncidenceList* inciNode = u->incidenceList->next;

        // 현재 정점(u)에 연결된 모든 간선을 순회
        while (inciNode != NULL) {
            // 간선의 다른 끝 정점(zN)을 가져옴
            int zN = G.Edge[inciNode->edge_index].v2_index;
            if (zN == u->num - 1) zN = G.Edge[inciNode->edge_index].v1_index;

            Vertices* z = &G.Vertices[zN];

            // u와 z에 연결된 간선 가중치 탐색
            int weight = -1;
            for (int i = 0; i < G.edge_num; i++) {
                if ((G.Edge[i].v1_index + 1 == u->num && G.Edge[i].v2_index + 1 == z->num) ||
                    (G.Edge[i].v2_index + 1 == u->num && G.Edge[i].v1_index + 1 == z->num)) {
                    weight = G.Edge[i].weight;
                    break; // 가중치를 찾았으므로 루프 종료
                }
            }

            // 우선순위 큐에 남아 있는 정점에 대해 거리 갱신
            for (int i = 0; i < n; i++) {
                if (z == Q[i]) {    // z가 큐에 존재할 경우
                    if (u->distance + weight < z->distance) {
                        z->distance = u->distance + weight; // 거리 갱신
                    }
                }
            }
            inciNode = inciNode->next;  // 다음 간선으로 이동
        }
    }

    free(Q);
}


// 우선순위 큐에서 최소 거리 정점 제거
Vertices* removeMin(Vertices** Q, int n) {
    int min_distance = 30000;
    int idx = -1;

    for (int i = 0; i < n; i++) {
        if ((*Q[i]).distance < min_distance) {
            min_distance = (*Q[i]).distance;
            idx = i;
        }
    }

    Vertices* tmp = Q[n - 1];
    Q[n - 1] = Q[idx];
    Q[idx] = tmp;

    return Q[n - 1];
}