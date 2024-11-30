//
// Created by 강민재 on 2024. 10. 15..
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    struct Node* parent;
    struct Node* leftChild;
    struct Node* rightChild;
    int key;
} Node;

int findElement(Node* root, int key);   // 현재 트리에서 키 k를 저장한 노드를 찾아 그 노드에 저장된 원소를 반환
Node* reduceExternal(Node* z);  // 노드 z의 부모노드 삭제
void expandExternal(Node* node);    // 노드를 확장

void insertItem(Node* root, int key);   // 현재 트리에 키 k를 저장한 새 노드를 삽입
Node* treeSearch(Node* node, int key);  // 현재 트리에서 키 k를 저장한 노드를 반환
int removeElement(Node* root, int key); // 현재 트리에서 키 k를 저장한 노드를 삭제한 후 원소를 반환
void printTree(Node* node); // 탐색트리 출력

Node* inOrderSucc(Node* node);  // 노드 w의 중위순회 후계자를 반환
Node* sibling(Node* node);  // 노드 w의 형제 노드를 반환

bool isExternal(Node* node);    // 노드 w가 외부노드인지 여부를 반환
bool isInternal(Node* node);    // 노드 w가 내부노드인지 여부를 반환
bool isRoot(Node* node);    // 노드 w가 루트노드인지 여부를 반환
void freeTree(Node* tree);  // 트리 메모리 해제

int main() {
    Node* root = NULL;
    root = (Node*)malloc(sizeof(Node));
    root->parent = NULL;
    root->key = - 1;

    char cmd;
    int key, element;

    while (1) {
        scanf("%c", &cmd);
        switch (cmd) {
            case 'q':   // 종료
                freeTree(root);
                return 0;
            case 'i':   // 삽입
                scanf("%d", &key);
                if (root->key != -1) insertItem(root, key);
                 else {
                     root->parent = NULL;
                     root->key = key;
                     expandExternal(root);
                 }

                break;
            case 's':   // 탐색
                scanf("%d", &key);
                element = findElement(root, key);
                if (element == -1) printf("X\n");
                else printf("%d\n", element);

                break;
            case 'p':   // 출력
                printTree(root);
                printf("\n");

                break;
            case 'd':   // 삭제
                scanf("%d", &key);
                element = removeElement(root, key);

                if (element == -1) printf("X\n");
                else printf("%d\n", element);

                break;
            default:
                break;
        }
    }
}

int findElement(Node* root, int key) {
    Node* node = treeSearch(root, key);

    if (isExternal(node)) return -1;    // 외부노드이면 -1 반환
    return node->key;   // 노드 키 반환
}

Node* reduceExternal(Node* z) {
    Node* w = z->parent;    // 부모 노드
    Node* zs = sibling(z);  // 형제 노드

    if (isRoot(w)) {    // 부모 노드가 루트 노드이면
        w = zs; // 부모 노드를 형제 노드로 변경
        zs->parent = NULL;  // 형제 노드의 부모를 NULL로 변경
    } else {    // 부모 노드가 루트 노드가 아니면
        Node* g = w->parent;    // 부모 노드의 부모 노드
        zs->parent = g; // 형제 노드의 부모를 g로 변경

        if (w == g->leftChild)  g->leftChild = zs;  // 부모 노드가 g 노드의 왼쪽 자식이었으면 g 노드의 왼쪽자식을 형제노드로 변경
        else g->rightChild = zs;    // 부모 노드가 g 노드의 오른쪽 자식이었으면 g 노드의 오른쪽 자식을 형제노드로 변경

    }

    free(z);
    free(w);

    return zs;  // 형제 노드 리턴
}

void expandExternal(Node* node) {
    // 왼쪽, 오른쪽 자식 노드 생성
    Node* leftChild = (Node*)malloc(sizeof(Node));
    Node* rightChild = (Node*)malloc(sizeof(Node));

    // 자식 노드 초기화
    leftChild->leftChild = leftChild->rightChild = NULL;
    rightChild->leftChild = rightChild->rightChild = NULL;

    // 자식 노드 연결
    leftChild->key = rightChild->key = -1;
    leftChild->parent = rightChild->parent = node;

    node->leftChild = leftChild;
    node->rightChild = rightChild;
}

void insertItem(Node* root, int key) {
    Node* node = treeSearch(root, key); // 삽입하려는 위치 찾기

    if (isInternal(node)) return;   // 삽입 위치가 내부노드이면 삽입 안하고 리턴
    else {  // 삽입 위치가 외부노드이면 노드 삽입 후 노드 확장
        node->key = key;
        expandExternal(node);
        return;
    }
}

Node* treeSearch(Node* node, int key) {
    if (isExternal(node)) return node;  // 외부노드이면 노드 반환

    if (node->key == key) return node;  // 찾으려는 노드와 현재 노드 키가 같으면 노드 반환
    else if (node-> key > key) return treeSearch(node->leftChild, key); // 찾으려는 노드 키가 현재 노드 키보다 작으면 왼쪽 자식 노드로 가서 함수 실행
    else return treeSearch(node->rightChild, key);  // 찾으려는 노드 키가 현재 노드 키보다 크면 왼쪽 자식 노드로 가서 함수 실행
}

int removeElement(Node* root, int key) {
    Node* node = treeSearch(root, key); // 제거하려는 노드 찾기

    if (isExternal(node)) return -1;  // 외부노드이면 -1 반환

    if (node == root && node->leftChild->key == -1 && node->rightChild->key == -1) {
        // 노드의 자식노드가 없으면 키만 변경
        node->key = -1;
    } else {
        // 자식노드 설정
        Node* childNode = node->leftChild;

        if (!isExternal(childNode))
            childNode = node->rightChild;

        // 자식 노드가 외부노드일 때
        if (isExternal(childNode)) {
            reduceExternal(childNode);  // 노드 축소
        } else {    // 자식 노드가 외부노드가 아닐 때
            Node* y = inOrderSucc(node);    // 삭제하려는 노드의 중위순회 노드 찾기
            childNode = y->leftChild;   // 중위순회 노드의 왼쪽 자식으로 자식 노드 설정
            node->key = y->key; // 삭제하려는 노드의 키를 중위순회 노드 키로 변경
            reduceExternal(childNode);  // childNode의 부모 노드 삭제
        }
    }

    return key;
}

void printTree(Node* node) {
    if (isExternal(node) || node->key == -1) return;    // 외부노드가 나오면 종료
    if (node != NULL) printf(" %d", node->key);

    // 재귀적으로 수행
    printTree(node->leftChild);
    printTree(node->rightChild);
}

Node* inOrderSucc(Node* node) {
    node = node->rightChild;    // 오른쪽 자식 노드로 이동

    if (isExternal(node)) return NULL;

    // 외부노드가 나오기 전까지 왼쪽 자식 노드로 이동
    while (isInternal(node->leftChild))
        node = node->leftChild;

    return node;
}

Node* sibling(Node* node) {
    if (isRoot(node)) return NULL;

    if (node->parent->leftChild == node) return node->parent->rightChild;
    else return node->parent->leftChild;
}

bool isExternal(Node* node) {
    return node->leftChild == NULL && node->rightChild == NULL;
}

bool isInternal(Node* node) {
    return node->leftChild != NULL || node->rightChild != NULL;
}

bool isRoot(Node* node) {
    return !node->parent;
}

void freeTree(Node* tree) {
    if (isExternal(tree)) return;
    else {
        freeTree(tree->leftChild);
        freeTree(tree->rightChild);
        free(tree);
    };
}