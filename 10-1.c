//
// Created by 강민재 on 2024. 10. 31..
//
#include <stdio.h>
#include <stdlib.h>

typedef struct vertices {
    int num;
    struct incidence* incidenceList;
} vertices;

typedef struct incidence {
    int edgeIdx;
    struct incidence* next;
} incidence;

typedef struct edge {
    int v1, v2;
    int weight;
} edge;

incidence* getIncidence(int edge);
void addIncidenceList(incidence* iH, int edgeIdx);
void reduceIncidenceList(incidence* iH, int edgeIdx);
void insertEdge(int v1_num, int v2_num, int weight, edge* e, vertices* v);
void printEdge(int a_num, vertices* v, edge* e);

int main() {
    vertices v[6];
    edge e[21];

    for (int i = 0; i < 6; i++) {
        v[i].num = i + 1;
        v[i].incidenceList = getIncidence(-1);
    }

    int k = 0;
    for (int i = 1; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            e[k].v1 = i;
            e[k].v2 = j;
            e[k++].weight = 0;
        }
    }

    insertEdge(1, 2, 1, e, v);
    insertEdge(1, 3, 1, e, v);
    insertEdge(1, 4, 1, e, v);
    insertEdge(1, 6, 2, e, v);
    insertEdge(2, 3, 1, e, v);
    insertEdge(3, 5, 4, e, v);
    insertEdge(5, 5, 4, e, v);
    insertEdge(5, 6, 3, e, v);

    while (1) {
        char cmd;
        scanf("%c", &cmd);

        if (cmd == 'q') return 0;

        if (cmd == 'm') {
            int a, b, m;
            scanf("%d %d %d", &a, &b, &m);
            insertEdge(a, b, m, e, v);
        }
        if (cmd == 'a') {
            int a;
            scanf("%d", &a);
            printEdge(a, v, e);
        }

        getchar();
    }
}

incidence* getIncidence(int edge) {
    incidence* newIncidence = (incidence*) malloc(sizeof(incidence));
    newIncidence->edgeIdx = edge;
    newIncidence->next = NULL;

    return newIncidence;
}

void addIncidenceList(incidence* iH, int edgeIdx) {
    while (iH->next != NULL && iH->next->edgeIdx < edgeIdx) {
        iH = iH->next;
    }

    incidence* newIncidence = getIncidence(edgeIdx);
    newIncidence->next = iH->next;
    iH->next = newIncidence;

    return;
}

void reduceIncidenceList(incidence* iH, int edgeIdx) {
    while (iH->next->edgeIdx != edgeIdx) {
        iH = iH->next;
    }

    incidence* tmp = iH->next;
    iH->next = tmp->next;

    free(tmp);
    return;
}

void insertEdge(int v1_num, int v2_num, int weight, edge* e, vertices* v) {
    if (v1_num > v2_num) {
        int tmp = v1_num;
        v1_num = v2_num;
        v2_num = tmp;
    }

    vertices v1 = {0, NULL};
    vertices v2 = {0, NULL};

    for (int i = 0; i < 6; i++) {
        if (v[i].num == v1_num) v1 = v[i];
        if (v[i].num == v2_num) v2 = v[i];
    }

    if (v1.num == 0 || v2.num == 0) {
        printf("-1\n");
        return;
    }

    int i;
    int prevWeight = 0;
    for (i = 0; i < 21; i++) {
        if (e[i].v1 == v1_num && e[i].v2 == v2_num) {
            prevWeight = e[i].weight;
            e[i].weight = weight;
            break;
        }
    }

    if (weight == 0) {
        if (v1_num != v2_num) reduceIncidenceList(v1.incidenceList, i);
        reduceIncidenceList(v2.incidenceList, i);
    } else if (!prevWeight) {
        if (v1_num != v2_num) addIncidenceList(v1.incidenceList, i);
        addIncidenceList(v2.incidenceList, i);
    }

    return;
}

void printEdge(int a_num, vertices* v, edge* e) {
    if (a_num < 1 || a_num > 6) {
        printf("-1\n");
        return;
    }

    incidence* iH = v[a_num - 1].incidenceList->next;

    while (iH != NULL) {
        int num = e[iH->edgeIdx].v1 == a_num ? e[iH->edgeIdx].v2 : e[iH->edgeIdx].v1;
        printf("%d %d ", num, e[iH->edgeIdx].weight);
        iH = iH->next;
    }

    printf("\n");
    return;
}