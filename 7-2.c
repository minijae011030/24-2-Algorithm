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
    int height;
} Node;

Node* root;

int findElement(int key);   // 현재 트리에서 키 k를 저장한 노드를 찾아 그 노드에 저장된 원소를 반환
void expandExternal(Node* node);    // 노드를 확장

void searchAndFixAfterInsertion(Node* node);    // 균형검사를 수행하고 불균형이 있으면 개조를 통해 높이균형 속성을 회복
bool updateHeight(Node* node);  // 노드 w의 높이를 (필요하면) 갱신한 후 갱신 여부를 반환
bool isBalanced(Node* node);    // 노드 w의 높이균형 여부를 반환
Node* restructure(Node* x, Node* y, Node* z);   // 3-노드 개조를 수행한 후 (갱신된) 3-노드의 루트를 반환

void insertItem(int key);   // 현재 트리에 키 k를 저장한 새 노드를 삽입
Node* treeSearch(Node* node, int key);  // 현재 트리에서 키 k를 저장한 노드를 반환
void printTree(Node* node); // 탐색트리 출력

Node* sibling(Node* node);  // 노드 w의 형제 노드를 반환
bool isExternal(Node* node);    // 노드 w가 외부노드인지 여부를 반환
bool isInternal(Node* node);    // 노드 w가 내부노드인지 여부를 반환
bool isRoot(Node* node);    // 노드 w가 루트노드인지 여부를 반환
void freeTree(Node* tree);  // 트리 메모리 해제

int main() {
    root = (Node*)malloc(sizeof(Node));
    root->parent = root->leftChild = root->rightChild = NULL;
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
                insertItem(key);
                break;
            case 's':   // 탐색
                scanf("%d", &key);
                element = findElement(key);

                if (element == -1) printf("X\n");
                else printf("%d\n", element);
                break;
            case 'p':   // 출력
                printTree(root);
                printf("\n");
                break;
            default:
                break;
        }
    }
}

int findElement(int key) {
    Node* node = treeSearch(root, key);

    if (isExternal(node)) return -1;     // 외부노드이면 -1 반환
    return node->key;   // 노드 키 반환
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

void searchAndFixAfterInsertion(Node* node) {
    Node *x, *y, *z;
    // 노드와 각 자식노드 높이 설정
    node->leftChild->height = 0;
    node->rightChild->height = 0;
    node->height = 1;

    // 노드의 부모노드가 없으면 종료
    if (node->parent == NULL) return;

    // 루트를 향해 올라가다가 처음 만나는 불균형 노드를 z로 설정
    z = node->parent;
    while (updateHeight(z) && isBalanced(z)) {
        if (z->parent == NULL) return;
        z = z->parent;
    }

    if (isBalanced(z)) return;  // 불균형 노드가 없으면 종료

    // z의 높은 자식을 y로 설정
    if (z->leftChild->height > z->rightChild->height) y = z->leftChild;
    else y = z->rightChild;

    // y의 높은 자식을 x로 설정
    if (y->leftChild->height > y->rightChild->height) x = y->leftChild;
    else x = y->rightChild;

    // x, y, z restructure 실행
    restructure(x, y, z);
}

bool updateHeight(Node* node) {
    // 노드의 왼쪽 자식과 오른쪽 자식의 높이를 비교하여 더 큰 값을 기준으로 현재 노드의 높이를 계산
    int height = ((node->leftChild->height) > (node->rightChild->height)) ?
            (node->leftChild->height + 1) : (node->rightChild->height + 1);

    // 현재 노드의 높이가 기존 높이와 다르면, 새로 계산된 높이로 갱신하고 true를 반환 (높이가 변경된 경우)
    if (height != node->height) {
        node->height = height;
        return true;
    }

    // 노드의 높이가 변경되지 않았으면 false를 반환
    return false;
}

bool isBalanced(Node* node) {
    // 노드의 왼쪽 자식과 오른쪽 자식의 높이 차이를 계산
    int value = node->leftChild->height - node->rightChild->height;

    // 높이 차이가 -1, 0, 1 범위 내에 있으면 이 노드는 균형 상태
    return ((value >= -1) && (value <= 1));
}

Node* restructure(Node* x, Node* y, Node* z) {
    Node* a, * b, * c;
    Node* T0, * T1, * T2, * T3;

    // x, y, z의 중위순회 방문 순서의 나열을 a, b, c로 설정
    // x, y, z의 부트리들 가운데 x, y, z를 루트로 하는 부트리를 제외한 4개의 부트리들의 중위순회 방문 순서의 나열을 T0, T1, T2, T3으로 설정
    if ((z->key < y->key) && (y->key < x->key)) {
        a = z, b = y, c = x;
        T0 = a->leftChild, T1 = b->leftChild, T2 = c->leftChild, T3 = c->rightChild;
    } else if ((x->key < y->key) && (y->key < z->key)) {
        a = x, b = y, c = z;
        T0 = a->leftChild, T1 = a->rightChild, T2 = b->rightChild, T3 = c->rightChild;
    } else if ((z->key < x->key) && (x->key < y->key)) {
        a = z, b = x, c = y;
        T0 = a->leftChild, T1 = b->leftChild, T2 = b->rightChild, T3 = c->rightChild;
    } else {
        a = y, b = x, c = z;
        T0 = a->leftChild, T1 = b->leftChild, T2 = b->rightChild, T3 = c->rightChild;
    }

    // z를 루트로 하는 부트리 b를 루트로 하는 부트리로 대체
    if (z->parent == NULL) {
        root = b;
        b->parent = NULL;
    } else if (z->parent->leftChild == z) {
        z->parent->leftChild = b;
        b->parent = z->parent;
    } else if (z->parent->rightChild == z) {
        z->parent->rightChild = b;
        b->parent = z->parent;
    }

    // T0과 T1을 각각 a의 왼쪽 및 오른쪽 부트리로 만든다
    a->leftChild = T0;
    a->rightChild = T1;
    T0->parent = T1->parent = a;
    updateHeight(a);

    // T2과 T3을 각각 c의 왼쪽 및 오른쪽 부트리로 만든다
    c->leftChild = T2;
    c->rightChild = T3;
    T2->parent = T3->parent = c;
    updateHeight(c);

    // a와 c를 각각 b의 왼쪽 및 오른쪽 부트리로 만든다
    b->leftChild = a;
    b->rightChild = c;
    a->parent = c->parent = b;
    updateHeight(b);

    return b;
}

void insertItem(int key) {
    Node* node = treeSearch(root, key); // 삽입하려는 위치 찾기

    if (isInternal(node)) return;   // 삽입 위치가 내부노드이면 삽입 안하고 리턴
    else {  // 삽입 위치가 외부노드이면 노드 삽입 후 노드 확장후 균형 복구
        node->key = key;
        expandExternal(node);
        searchAndFixAfterInsertion(node);
        return;
    }
}

Node* treeSearch(Node* node, int key) {
    if (isExternal(node)) return node;

    if (node->key == key) return node;
    else if (node-> key > key) return treeSearch(node->leftChild, key);
    else return treeSearch(node->rightChild, key);
}

void printTree(Node* node) {
    if (isExternal(node) || node->key == -1) return;
    printf(" %d", node->key);

    printTree(node->leftChild);
    printTree(node->rightChild);
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
    return node->parent == NULL;
}

void freeTree(Node* tree) {
    if (isExternal(tree)) return;
    else {
        freeTree(tree->leftChild);
        freeTree(tree->rightChild);
        free(tree);
    };
}