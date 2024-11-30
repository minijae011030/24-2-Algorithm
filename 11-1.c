//
// Created by 강민재 on 2024. 11. 8..
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Vertices {
    struct Incidence* inciList;
    int num;
    bool isFresh;   // true: fresh, false: visited
} Vertices;

typedef struct Incidence {
    int edgeIdx;
    struct Incidence* next;
} Incidence;

typedef struct Edge {
    int v1, v2;
    bool isFresh;   // true: fresh, false: visited
    bool treeOrBack;    // true: tree, false: back
} Edge;

int n, m;

Incidence * getInciList(int idx);
void insertEdge(int v1_num, int v2_num, Edge* edge, Vertices* vertices);
void addIncidenceList(Edge* edge, Incidence* iH, int edgeIdx, int value, int insertValue);

void DFS(Vertices* vertices, Edge* edge, int startVertice);
void rDFS(Vertices* vertices, Vertices* startVertice, Edge* edge);

int main() {
    int s;  // n: 정점의 개수, m: 간선의 개수, s: 순회 시작 정점 번호
    scanf("%d %d %d", &n, &m, &s);

    Vertices* vertices = (Vertices*)malloc(sizeof(Vertices) * n);
    Edge * edge = (Edge*)malloc(sizeof(Edge) * m);

    for (int i = 0; i < n; i++) {   // 노드 초기화
        vertices[i].num = i + 1;
        vertices[i].inciList = getInciList(-1);
    }

    for (int i = 0; i < m; i++) {   // 간선 리스트 초기화
        edge[i].v1 = edge[i].v2 = -1;
    }

    int v1, v2;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &v1, &v2);
        insertEdge(v1, v2, edge, vertices);
    }

    DFS(vertices, edge, s);

    return 0;
}

Incidence * getInciList(int idx) {
    Incidence* newInciList = (Incidence*) malloc(sizeof(Incidence));
    newInciList->edgeIdx = idx;
    newInciList->next = NULL;

    return newInciList;
}

void insertEdge(int v1_num, int v2_num, Edge* edge, Vertices* vertices) {
  if (v1_num > v2_num) {
      int tmp = v1_num;
      v1_num = v2_num;
      v2_num = tmp;
  }

  // 노드 생성
  Vertices v1, v2;

  // 노드 리스트에서 노드 찾기
  for (int i = 0; i < n; i++) {
      if (vertices[i].num == v1_num) v1 = vertices[i];
      if (vertices[i].num == v2_num) v2 = vertices[i];
  }

  // 간선 추가
  for (int i = 0; i < m; i++) {
      if (edge[i].v1 == -1 && edge[i].v2 == -1) {
          edge[i].v1 = v1_num;
          edge[i].v2 = v2_num;

          addIncidenceList(edge, v1.inciList, i, v1_num, v2_num);
          if (v1_num != v2_num) addIncidenceList(edge, v2.inciList, i, v2_num, v1_num);
          break;
      }
  }
}

void addIncidenceList(Edge* edge, Incidence* iH, int edgeIdx, int value, int insertValue) {
    Incidence* newIncidence = getInciList(edgeIdx);
    int opposeValue;

    while (iH->next != NULL) {
        opposeValue = edge[iH->next->edgeIdx].v1 == value ?
                edge[iH->next->edgeIdx].v2 : edge[iH->next->edgeIdx].v1;
        if (opposeValue > insertValue) break;
        iH = iH->next;
    }

    newIncidence->next = iH->next;
    iH->next = newIncidence;

    return;
}

// 깊이 우선 탐색 (DFS) 수행 함수
void DFS(Vertices* vertices, Edge* edge, int startVertice) {
    // 모든 정점과 간선을 미방문 상태로 초기화
    for (int i = 0; i < n; i++) vertices[i].isFresh = true;
    for (int i = 0; i < m; i++) edge[i].isFresh = true;

    // 시작 정점에서부터 DFS 탐색 수행
    for (int i = startVertice - 1; i < n; i++) {
        if (vertices[i].isFresh) {
            printf("%d\n", vertices[i].num);
            rDFS(vertices, &vertices[i], edge);
        }
    }

    // 탐색 시작 정점 이전의 정점들에 대해 DFS 수행
    for (int i = 0; i < startVertice - 1; i++) {
        if (vertices[i].isFresh) {
            printf("%d\n", vertices[i].num);
            rDFS(vertices, &vertices[i], edge);
        }
    }
}

// 재귀적으로 깊이 우선 탐색을 수행하는 함수
void rDFS(Vertices* vertices, Vertices* startVertice, Edge* edge) {
    startVertice->isFresh = false;  // 현재 정점을 방문으로 표시

    Incidence* inciList = startVertice->inciList;

    // 인접 리스트를 따라가며 간선을 탐색
    while (inciList->next != NULL) {
        inciList = inciList->next;
        if (edge[inciList->edgeIdx].isFresh) {  // 간선이 미방문 상태라면
            edge[inciList->edgeIdx].isFresh = false;  // 간선을 방문으로 표시

            int opposeNodeNum = startVertice->num == edge[inciList->edgeIdx].v1 ?
                                edge[inciList->edgeIdx].v2 : edge[inciList->edgeIdx].v1;
            Vertices * opposeVertice;
            for (int i = 0; i < n; i++) {
                if (opposeNodeNum == vertices[i].num)
                    opposeVertice = &vertices[i];
            }

            // 인접한 정점이 미방문 상태이면 트리 간선으로 처리
            if (opposeVertice->isFresh) {
                edge[inciList->edgeIdx].treeOrBack = true;
                printf("%d\n", opposeVertice->num);
                rDFS(vertices, opposeVertice, edge);
            } else {
                // 이미 방문한 정점이라면 백 간선으로 처리
                edge[inciList->edgeIdx].treeOrBack = false;
            }
        }
    }
}