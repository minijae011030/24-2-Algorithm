//
// Created by 강민재 on 2024. 11. 15..
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Vertices {
    char name;
    int inDegree;	// 진입차수
    struct IncidenceList* fromInciList;	// 진입 간선
    struct IncidenceList* toInciList;	// 진출 간선
}Vertices;

typedef struct IncidenceList {
    int edgeIdx;
    struct IncidenceList* next;
}IncidenceList;

typedef struct Edge {
    int fromIdx;
    int toIdx;
}Edge;

typedef struct Graph {
    struct Vertices* vertices;
    struct Edge* edge;
    int verticeNum;
    int edgeNum;
}Graph;

Graph buildGraph();
IncidenceList* getInciList(int edgeIdx);
int index(Graph G, char verticeName);

char* topologicalSort(Graph G);

int main() {
    Graph G = buildGraph();

    char* topOrder = topologicalSort(G);
    if (!topOrder[0]) printf("0");
    else for (int i = 0; i < G.verticeNum; i++) printf("%c ", topOrder[i + 1]);
}

Graph buildGraph() {
    Graph G;

    scanf("%d", &G.verticeNum);	// 정점 개수 입력
    getchar();

    G.vertices = (Vertices*)malloc(sizeof(Vertices) * G.verticeNum);
    for (int i = 0; i < G.verticeNum; i++) {
        scanf(" %c", &G.vertices[i].name);
        getchar();
        G.vertices[i].fromInciList = getInciList(-1);
        G.vertices[i].toInciList = getInciList(-1);
        G.vertices[i].inDegree = 0;
    }

    scanf("%d", &G.edgeNum);	// 간선 개수 입력
    G.edge = (Edge*)malloc(sizeof(Edge) * G.edgeNum);

    char v1, v2;
    for (int i = 0; i < G.edgeNum; i++) {
        scanf(" %c %c", &v1, &v2);


        int v1Idx = index(G, v1);	// from index
        int v2Idx = index(G, v2);	// to index

        G.vertices[v2Idx].inDegree++;

        G.edge[i].fromIdx = v1Idx;
        G.edge[i].toIdx = v2Idx;

        IncidenceList* v1InciHead = G.vertices[v1Idx].toInciList;
        IncidenceList* v2InciHead = G.vertices[v2Idx].fromInciList;

        IncidenceList* v1NewInciNode = getInciList(i);
        IncidenceList* v2NewInciNode = getInciList(i);

        v1NewInciNode->next = v1InciHead->next;
        v1InciHead->next = v1NewInciNode;

        v2NewInciNode->next = v2InciHead->next;
        v2InciHead->next = v2NewInciNode;
    }

    return G;
}

IncidenceList* getInciList(int edgeIdx) {
    IncidenceList* newInciNode = (IncidenceList*)malloc(sizeof(IncidenceList));
    newInciNode->edgeIdx = edgeIdx;
    newInciNode->next = NULL;

    return newInciNode;
}

int index(Graph G, char verticeName) {
    for (int i = 0; i < G.verticeNum; i++)
        if (G.vertices[i].name == verticeName)
            return i;
}

/**
 * G로부터 위상순서를 구하거나 방향싸이클이 존재함을 보고
 * @param G: 방향그래프
 * @return topOrder: 위상 순서
 */
char* topologicalSort(Graph G) {
    Vertices* Q[100];   // 정점들의 대기열

    int startIdx = 0, endIdx = 0;

    // 모든 정점에 대해 정점 번호순으로 반복
    for (int i = 0; i < G.verticeNum; i++) {
        if (G.vertices[i].inDegree == 0) {  // 진입차수가 0인 정점들을 Q에 삽입
            Q[endIdx++] = &G.vertices[i];
        }
    }


    char* topOrder = (char*)malloc(sizeof(char) * (G.verticeNum + 1));
    int order = 1;  // order: 위상순위

    while (startIdx != endIdx) {    // Q가 비지 않은 동안 반복
        Vertices* u = Q[startIdx++];    // dequeue
        topOrder[order++] = u->name;    // 위상순위 order의 정점 저장 및 위상순위 order 증가

        IncidenceList* inciNode = u->toInciList; // u의 모든 진출간선에 대해 반복
        while (inciNode->next != NULL) {
            inciNode = inciNode->next;
            Vertices* w = &G.vertices[G.edge[inciNode->edgeIdx].toIdx]; // w: 간선의 종점

            w->inDegree--;  // w의 진입차수 감소
            if (w->inDegree == 0)     // 정점 w의 진입차수가 0 이면 Q에 삽입
                Q[endIdx++] = w;
        }
    }

    if (order <= G.verticeNum) topOrder[0] = 0; // G가 non-DAG인 경우
    else topOrder[0] = 1;   // G가 DAG인 경우

    return topOrder;
}