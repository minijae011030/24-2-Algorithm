//
// Created by 강민재 on 2024. 10. 31..
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int v1, v2;
    int weight;
} Edge;

void insertEdge(int v1, int v2, Edge* edge, int** arr , int weight);
void modifyWeight(int v1, int v2, Edge* edge, int** arr, int weight);
void printEdge(Edge* edge, int** arr, int v);

int main() {
    int verticeArr[6];
    int** adjacencyMatrix;
    Edge edge[21];

    for (int i = 0; i < 6; i++) {
        verticeArr[i] = i + 1;
    }

    adjacencyMatrix = (int**)malloc(6 * sizeof(int*));
    for (int i = 0; i < 6; i++) {
        adjacencyMatrix[i] = (int*)malloc(6 * sizeof(int));
        for (int j = 0; j < 6; j++) {
            adjacencyMatrix[i][j] = -1;
        }
    }

    int k = 0;
    for (int i = 1; i < 6; i++) {
        for (int j = i; j <= 6; j++) {
            edge[k].v1 = i;
            edge[k].v2 = j;
            edge[k++].weight = 0;
        }
    }

    insertEdge(1, 2, edge, adjacencyMatrix, 1);
    insertEdge(1, 3, edge, adjacencyMatrix, 1);
    insertEdge(1, 4, edge, adjacencyMatrix, 1);
    insertEdge(1, 6, edge, adjacencyMatrix, 2);
    insertEdge(2, 3, edge, adjacencyMatrix, 1);
    insertEdge(3, 5, edge, adjacencyMatrix, 4);
    insertEdge(5, 5, edge, adjacencyMatrix, 4);
    insertEdge(5, 6, edge, adjacencyMatrix, 3);

    while (1) {
        char cmd;
        scanf("%c", &cmd);
        if (cmd == 'q') return 0;

        if (cmd == 'm') {
            int a, b, m;
            scanf("%d %d %d", &a, &b, &m);
            if ((a >= 1 && a <= 6) && (b >= 1 && b <= 6))
                modifyWeight(a, b, edge, adjacencyMatrix, m);
            else
                printf("-1\n");
        }

        if (cmd == 'a') {
            int a;
            scanf("%d", &a);
            if (a >= 1 && a <= 6)
                printEdge(edge, adjacencyMatrix, a);
            else
                printf("-1\n");
        }
        getchar();
    }

}

void insertEdge(int v1, int v2, Edge* edge, int** arr , int weight) {
    if (v1 > v2) {
        int tmp = v1;
        v1 = v2;
        v2 = tmp;
    }

    int i;
    for (i = 0; i < 21; i++) {
        if (edge[i].v1 == v1 && edge[i].v2 == v2) {
            edge[i].weight = weight;
            break;
        }
    }
    arr[v1-1][v2-1] = arr[v2-1][v1-1] = i;
}

void modifyWeight(int v1, int v2, Edge* edge, int** arr, int weight) {
    if (v1 > v2) {
        int tmp = v1;
        v1 = v2;
        v2 = tmp;
    }

    if (weight == 0) {
        edge[arr[v1-1][v2-1]].weight = 0;
        arr[v1-1][v2-1] = arr[v2-1][v1-1] = -1;
    } else {
        int i;
        for (i = 0; i < 21; i++) {
            if (edge[i].v1 == v1 && edge[i].v2 == v2) {
                break;
            }
        }

        arr[v1-1][v2-1] = arr[v2-1][v1-1] = i;
        edge[i].weight = weight;
    }
}

void printEdge(Edge* edge, int** arr, int v) {
    for (int i = 0; i < 6; i++) {
        if (arr[v-1][i] != -1) {
            int oppose = edge[arr[v-1][i]].v1 == v ?
                    edge[arr[v-1][i]].v2 : edge[arr[v-1][i]].v1;
            printf(" %d %d", oppose, edge[arr[v-1][i]].weight);
        }
    }
    printf("\n");
}