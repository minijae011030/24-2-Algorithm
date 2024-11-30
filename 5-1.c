//
// Created by 강민재 on 2024. 9. 30..
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} NODE;

void partition(NODE* L, NODE** L1, NODE** L2, int n);	// 단일연결리스트를 두 개의 부리스트로 분할
NODE* merge(NODE** L1, NODE** L2);	// 두개의 부 리스트 합병
void mergeSort(NODE** L, int n);	// 단일연결리스트의 원소들을 합병정렬

void addList(NODE** L, int value);	// 단일연결리스트에 노드 추가
void printList(struct node* L);	// 단일연결리스트 출력
void deleteList(struct node* L);	// 단일연결리스트 메모리 해제

int main() {
    int n, value;
    NODE* L = NULL; // 연결리스트 포인터

    scanf("%d", &n);    // 원소 개수 입력

    // 입력받은 값 리스트에 추가
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        addList(&L, value);
    }

    // 병합 정렬
    mergeSort(&L, n);
    // 정렬된 연결리스트 출력
    printList(L);
    // 연결리스트 메모리 해제
    deleteList(L);

    return 0;
}

void partition(NODE* L, NODE** L1, NODE** L2, int n) {
    NODE* p = L;
    *L1 = L;    // 첫번재 부리스트는 원래 리스트의 처음부터 시작

    // n/2만큼 연결리스트 이동
    for (int i = 0; i < (n / 2) - 1; i++) {
        p = p->next;
    }

    // 부리스트 L1, L2로 분할
    *L2 = p->next;
    p->next = NULL;
}

NODE* merge(NODE** L1, NODE** L2) {
    NODE* p, * L;
    NODE* A = *L1;
    NODE* B = *L2;

    // 두 리스트 중 작은 값을 가진 노드를 결과 리스트의 첫 번째 노드로 설정
    if (A->data <= B->data) {
        L = A;
        A = A->next;
        p = L;
    }
    else {
        L = B;
        B = B->next;
        p = L;
    }

    // 나머지 노드를 하나씩 비교해 합병
    while ((A != NULL) && (B != NULL)) {
        if (A->data <= B->data) {
            p->next = A;
            A = A->next;
            p = p->next;
        }
        else {
            p->next = B;
            B = B->next;
            p = p->next;
        }
    }

    // 나머지 원소들 병합된 연결리스트 뒤로 추가
    while (A != NULL) {
        p->next = A;
        p = A;
        A = A->next;
    }

    while (B != NULL) {
        p->next = B;
        p = B;
        B = B->next;
    }

    return L;
}

void mergeSort(NODE** L, int n) {
    NODE* L1, * L2, * p = *L;

    if (n > 1) {    // 리스트의 크기가 1 이하일 때는 정렬할 필요 없음
        partition(p, &L1, &L2, n);  // 리스트 분할

        // 리스트 크기에 따라 정렬
        if ((n % 2) == 0) {
            mergeSort(&L1, n / 2);
            mergeSort(&L2, n / 2);
        }
        else {
            mergeSort(&L1, n / 2);
            mergeSort(&L2, (n / 2) + 1);
        }

        // 정렬된 부리스트 합병
        *L = merge(&L1, &L2);
    }
}

void addList(NODE** L, int value) {
    NODE* p = *L;

    NODE* newnode = (NODE*)malloc(sizeof(NODE));
    newnode->data = value;
    newnode->next = NULL;

    if (*L == NULL) {
        *L = newnode;
    }
    else {
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newnode;
    }
}

void printList(struct node* L) {
    struct node* p = L;

    while (p != NULL) {
        printf(" %d", p->data);
        p = p->next;
    }

    printf("\n");
}

void deleteList(struct node* L) {
    struct node* p = L;

    while (p != NULL) {
        L = L->next;
        free(p);
        p = L;
    }
}