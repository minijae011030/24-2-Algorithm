//
// Created by 강민재 on 2024. 10. 29..
//
#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0

int M, n, q;
int *hashTable; // 해시 테이블

int hash1(int key);
int hash2(int key);
void insertItem(int key);
void searchItem(int key);
void printTable();

int main() {
    scanf("%d %d %d", &M, &n, &q); // M, n, q 입력

    hashTable = (int *)malloc(sizeof(int) * M);
    for (int i = 0; i < M; i++) {
        hashTable[i] = EMPTY; // 해시 테이블 초기화
    }

    char cmd;
    int key;

    while (1) {
        scanf("%c", &cmd);

        switch (cmd) {
            case 'e':
                printTable();
                free(hashTable);
                return 0;
            case 'i': // 삽입
                scanf("%d", &key);
                insertItem(key);
                break;
            case 's': // 탐색
                scanf("%d", &key);
                searchItem(key);
                break;
            case 'p': // 출력
                printTable();
                break;
            default:
                break;
        }
    }

}

int hash1(int key) {
    return key % M;
}

// 두 번째 해시 함수
int hash2(int key) {
    return q - (key % q);
}

// 삽입 함수
void insertItem(int key) {
    int idx = hash1(key);
    int step = hash2(key);
    int originalIdx = idx;

    for (int i = 0; i < M; i++) {
        if (hashTable[idx] == EMPTY) {
            hashTable[idx] = key;
            printf("%d\n", idx);
            return;
        }
        if (i > 0) {
            printf("C");
        }
        idx = (originalIdx + i * step) % M;
    }
}

// 탐색 함수
void searchItem(int key) {
    int idx = hash1(key);
    int step = hash2(key);
    int i, originalIdx = idx;

    for (i = 0; i < M; i++) {
        if (hashTable[idx] == key) {
            printf("%d %d\n", idx, key);
            return;
        } else if (hashTable[idx] == EMPTY) {
            break;
        }
        idx = (originalIdx + i * step) % M; // 이중 해싱으로 위치 이동
    }

    // 키가 존재하지 않음
    printf("-1\n");
}

// 해시 테이블 출력
void printTable() {
    for (int i = 0; i < M; i++) {
        if (hashTable[i] == EMPTY) {
            printf(" 0");
        } else {
            printf(" %d", hashTable[i]);
        }
    }
    printf("\n");
}