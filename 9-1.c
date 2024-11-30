//
// Created by 강민재 on 2024. 10. 27..
//

#include <stdio.h>
#include <stdlib.h>
typedef struct Bucket {
    int index;
    struct Node* head;
} Bucket;

typedef struct Node {
    struct Node* next;
    int key;
} Node;

int n;

int hash(int key);
Node* makeNode(int key);
void insertNode(Bucket* arr, int key);
int searchNode(Bucket* arr, int key);
int deleteNode(Bucket* arr, int key);
void printBucket(Bucket* arr);

int main() {
    scanf("%d", &n);

    Bucket* arr = (Bucket*)malloc(sizeof(Bucket) * n);
    for (int i = 0; i < n; i++) {
        arr[i].index = i;
        arr[i].head = NULL;
    }

    char cmd;
    int key;

    while (1) {
        scanf("%c", &cmd);
        switch (cmd) {
            case 'e':
                return 0;
            case 'i':
                scanf("%d", &key);
                insertNode(arr, key);
                break;
            case 's':
                scanf("%d", &key);
                printf("%d\n", searchNode(arr, key));
                break;
            case 'd':
                scanf("%d", &key);
                printf("%d\n", deleteNode(arr, key));
                break;
            case 'p':
                printBucket(arr);
                break;
            default:
                break;
        }
    }
}

int hash(int key) {
    return key % n;
}

Node* makeNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;

    return newNode;
}

void insertNode(Bucket* arr, int key) {
    int idx = hash(key);
    Node* newNode = makeNode(key);

    Node* head = arr[idx].head;

    if (head) {
        newNode->next = head;
        arr[idx].head = newNode;
    } else {
        arr[idx].head = newNode;
    }

    return;
}

int searchNode(Bucket* arr, int key) {
    int idx = hash(key);
    Node* node = arr[idx].head;

    int rank = 1;

    while (node != NULL) {
        if (node->key == key) {
            return rank;
        }
        node = node->next;
        rank++;
    }

    return 0;

}

int deleteNode(Bucket* arr, int key) {
    int idx = hash(key);
    Node* node = arr[idx].head;
    Node* prev = NULL;

    int rank = 1;
    while (node != NULL) {
        if (node->key == key) {
            if (prev == NULL) { // Key is at the head
                arr[idx].head = node->next;
            } else {
                prev->next = node->next;
            }
            free(node); // Free the memory
            return rank;
        }
        prev = node;
        node = node->next;
        rank++;
    }

    return 0;
}

void printBucket(Bucket* arr) {
    for (int i = 0; i < n; i++) {
        Node* head = arr[i].head;

        while (head != NULL) {
            printf(" %d", head->key);
            head = head->next;
        }
    }
    printf("\n");
}