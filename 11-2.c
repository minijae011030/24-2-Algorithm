//
// Created by 강민재 on 2024. 11. 8..
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Vertices {
    int node;
    bool isFresh;
} Vertices;

typedef struct Edgee {
    int v1, v2;
    bool isFresh, treeOrCross;
} Edge;

int n, m;

void BFS(Vertices* vertice, Edge* edge, int* adjMatrix, int startIdx);
void BFS1(Vertices* vertice, Vertices startVertice, Edge* edge, int** adjMatrix);

int main() {
    int s;
    scanf("%d %d %d", &n, &m, &s);

    // 노드 초기화
    Vertices* vertice = (Vertices*)malloc(sizeof(Vertices) * n);
    for (int i = 0; i < n; i++) vertice[i].node = i + 1;

    // 간선 초기화
    Edge* edge = (Edge*)malloc(sizeof(Edge) * m);
    for (int i = 0; i < m; i++) edge[i].v1 = edge[i].v2 = -1;

    // 인접 행렬 초기화
    int** adjacencyMatrix = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < m; i++) adjacencyMatrix[i] = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adjacencyMatrix[i][j] = -1;

    // 노드 입력받고 간선 추가
    int v1, v2;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &v1, &v2);

        v1--;
        v2--;
        edge[i].v1 = v1;
        edge[i].v2 = v2;

        adjacencyMatrix[v1][v2] = adjacencyMatrix[v2][v1] = i;
    }

    BFS(vertice, edge, adjacencyMatrix, s);

    return 0;
}

// 시작 정점에서 연결된 모든 노드를 순차적으로 방문
void BFS(Vertices* vertice, Edge* edge, int* adjMatrix, int startIdx) {
    for (int i = 0; i < n; i++) vertice[i].isFresh = true;  // 모든 정점을 미방문 상태로 초기화
    for (int i = 0; i < m; i++) edge[i].isFresh = true;     // 모든 간선을 미방문 상태로 초기화
    startIdx--;

    // 시작 정점부터 차례로 BFS1 호출 (탐색 시작)
    for (int i = startIdx; i < n; i++) {
        if (vertice[i].isFresh) {
            printf("%d\n", vertice[i].node);  // 방문 정점 출력
            BFS1(vertice, vertice[i], edge, adjMatrix);
        }
    }

    // 탐색 시작 정점 이전의 정점들에 대해 BFS1 호출
    for (int i = 0; i < startIdx; i++) {
        if (vertice[i].isFresh) {
            printf("%d\n", vertice[i].node);  // 방문 정점 출력
            BFS1(vertice, vertice[i], edge, adjMatrix);
        }
    }
}

// 재귀적으로 BFS를 수행하는 함수
void BFS1(Vertices* vertice, Vertices startVertice, Edge* edge, int** adjMatrix) {
    Vertices* verticeList = (Vertices*)malloc(sizeof(Vertices) * n);
    verticeList[0] = startVertice;  // 탐색을 시작할 정점을 리스트에 추가
    int verticeListLength = 1;

    // 탐색할 정점이 없을 때까지 반복
    while (1) {
        if (verticeListLength == 0) return;  // 방문할 정점이 없으면 종료

        Vertices* nextVerticeList = (Vertices*)malloc(sizeof(Vertices) * n);  // 다음 레벨의 정점 리스트
        int newVerticeListLength = 0;

        // 현재 레벨의 모든 정점을 탐색
        for (int i = 0; i < verticeListLength; i++) {
            int matrixIdx = verticeList[i].node - 1;  // 정점 번호를 인덱스로 변환
            for (int j = 0; j < n; j++) {
                if (adjMatrix[matrixIdx][j] != -1) {  // 연결된 간선이 존재하는 경우
                    int edgeIdx = adjMatrix[matrixIdx][j];

                    if (edge[edgeIdx].isFresh) {  // 미방문 간선이라면
                        edge[edgeIdx].isFresh = false;  // 간선을 방문 처리
                        int verticeIdx = verticeList[i].node - 1 == edge[edgeIdx].v1 ?
                                         edge[edgeIdx].v2 : edge[edgeIdx].v1;
                        Vertices* opposeVertice = &vertice[verticeIdx];  // 반대편 정점

                        if (opposeVertice->isFresh) {  // 반대편 정점이 미방문 상태라면
                            printf("%d\n", opposeVertice->node);  // 방문 정점 출력
                            opposeVertice->isFresh = false;  // 반대편 정점을 방문 처리
                            edge[edgeIdx].treeOrCross = true;  // 트리 간선으로 분류
                            nextVerticeList[newVerticeListLength] = *opposeVertice;  // 다음 레벨에 추가
                            newVerticeListLength++;
                        } else {
                            edge[edgeIdx].treeOrCross = false;  // 이미 방문한 정점이면 교차 간선으로 분류
                        }
                    }
                }
            }
        }

        verticeListLength = newVerticeListLength;  // 다음 레벨의 정점 리스트로 업데이트
        verticeList = nextVerticeList;
    }
}