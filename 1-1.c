//
// Created by 강민재 on 2024. 11. 30..
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char element;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct LinkedList {
    struct Node* header;
    struct Node* trailer;
} LinkedList;

LinkedList initLinkedList();    // 연결리스트 초기화
Node* CreateNewNode(char element);  // 새로운 노드 생성
void add(LinkedList* L, int rank, char element); // 연결리스트에 노드 추가
void delete(LinkedList* L, int rank);    // 연결리스트에서 노드 삭제
void get(LinkedList* L, int rank);  // 연결리스트에서 특정 노드의 원소 반환
void print(LinkedList* L);   // 연결리스트 출력

int main() {
    LinkedList L = initLinkedList();

    int n, rank;
    char command, element;

    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        scanf("%c", &command);
        getchar();

        if (command == 'A') {
            scanf("%d %c", &rank, &element);
            getchar();

            add(&L, rank, element);
        } else if (command == 'D') {
            scanf("%d", &rank);
            getchar();

            delete(&L, rank);
        } else if (command == 'G') {
            scanf("%d", &rank);
            getchar();

            get(&L, rank);
        } else {
            print(&L);
        }
    }

    return 0;
}

LinkedList initLinkedList() {
    LinkedList L;

    L.header = (Node*)malloc(sizeof(Node));
    L.trailer = (Node*)malloc(sizeof(Node));

    L.header->prev = NULL;
    L.header->next = L.trailer;

    L.trailer->prev = L.header;
    L.trailer->next = NULL;

    return L;
}

Node* CreateNewNode(char element) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->prev = NULL;
    newNode->next = NULL;
    newNode->element = element;

    return newNode;
}

void add(LinkedList* L, int rank, char element) {
    Node* p = L->header;

    for (int i = 0; i < rank; i++) {
        if (p == L->trailer) {

            printf("invalid position\n");
            return;
        }

        p = p->next;
    }
    p = p->prev;

    Node* newNode = CreateNewNode(element);

    newNode->next = p->next;
    newNode->prev = p;

    p->next->prev = newNode;
    p->next = newNode;

    return;
}

void delete(LinkedList* L, int rank) {
    Node* p = L->header;

    for (int i = 0; i < rank; i++) {
        p = p->next;

        if (p == L->trailer) {
            printf("invalid position\n");
            return;
        }
    }

    p->prev->next = p->next;
    p->next->prev = p->prev;

    free(p); // 메모리 해제

    return;
}

void get(LinkedList* L, int rank) {
    Node *p = L->header;

    for (int i = 0; i < rank; i++) {
        p = p->next;

        if (p == L->trailer) {

            printf("invalid position\n");
            return;
        }
    }

    printf("%c\n", p->element);
}

void print(LinkedList* L) {
    Node* node = L->header->next;

    while (node != L->trailer) {
        printf("%c", node->element);
        node = node->next;
    }

    printf("\n");

    return;
}