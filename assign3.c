//
// Created by 강민재 on 2024. 11. 6..
//
#include <stdio.h>
#include <stdlib.h>

int MAX = 23;

int hash(int key);
int hash2(int key);
int findElement(int* H, int key);
void insertItem(int* H, int key);
int removeElement(int* H, int key);
void printHashTable(int* H);

int main() {
    int* HashTable = (int*)malloc(sizeof(int) * MAX);
    for (int i = 0; i < MAX; i++)
        HashTable[i] = -1;

    char cmd;
    int key, result;
    while (1) {
        scanf("%c", &cmd);
        switch (cmd) {
            case 'q':
                free(HashTable);
                return 0;
            case 'f':
                scanf("%d", &key);
                getchar();
                result = findElement(HashTable, key);
                if (result == -1) printf("NoSuchKey\n");
                else printf("%d\n", result);
                break;
            case 'i':
                scanf("%d", &key);
                getchar();
                insertItem(HashTable, key);
                break;
            case 'r':
                scanf("%d", &key);
                getchar();
                result = removeElement(HashTable, key);
                if (result == -1) printf("NoSuchKey\n");
                else printf("%d\n", result);
                break;
            case 'p':
                getchar();
                printHashTable(HashTable);
                break;
            default:
                break;
        }
    }
}

int hash(int key) {
    return key % MAX;
}

int hash2(int key) {
    return 1 + (key % (MAX - 1));
}

int findElement(int* H, int key) {
    int index = hash(key);
    int step = hash2(key);
    int originalIndex = index;

    for (int i = 0; i < MAX; i++) {
        if (H[index] == key) {
            return key;
        }
        if (H[index] == -1) {  // 빈 셀 만나면 종료
            break;
        }
        index = (originalIndex + i * step) % MAX;
    }

    return -1;  // NoSuchKey
}

void insertItem(int* H, int key) {
    int index = hash(key);
    int step = hash2(key);
    int originalIndex = index;

    for (int i = 0; i < MAX; i++) {
        // 이미 해당 키가 존재하는 경우
        if (H[index] == key) {
            printf("Duplicate key\n");
            return;
        }
        // 빈 자리를 찾은 경우
        if (H[index] == -1 || H[index] == -2) {
            H[index] = key;
            return;
        }
        // 충돌 시 이중 해싱을 통한 다음 위치 계산
        index = (originalIndex + i * step) % MAX;
    }

    printf("Hash table is full\n");
}

int removeElement(int* H, int key) {
    int index = hash(key);
    int step = hash2(key);
    int originalIndex = index;

    for (int i = 0; i < MAX; i++) {
        // 키를 찾은 경우
        if (H[index] == key) {
            H[index] = -2;  // -2는 비활성화된 셀
            return key;
        }
        // 빈 셀을 만난 경우 탐색 중단
        if (H[index] == -1) {
            break;
        }
        // 충돌 시 이중 해싱을 통한 다음 위치 계산
        index = (originalIndex + i * step) % MAX;
    }

    return -1;  // NoSuchKey
}

void printHashTable(int* H) {
    for (int i = 0; i < MAX; i++) printf("%d ", i);
    printf("\n");
    for (int i = 0; i < MAX; i++) {
        if (H[i] == -1 || H[i] == -2) printf(". ");
        else printf("%d ", H[i]);
    }
    printf("\n");
}