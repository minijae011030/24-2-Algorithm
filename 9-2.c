//
// Created by 강민재 on 2024. 10. 29..
//
#include <stdio.h>
#include <stdlib.h>

int hash(int m, int id);
int insertItem(int* arr, int m, int id);
void searchItem(int* arr, int m, int id);

int main() {
    int m, n, id;
    char cmd;
    scanf("%d %d", &m, &n);

    int* arr = (int*)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) arr[i] = 0;

    while (1) {
        scanf("%c", &cmd);
        switch (cmd)
        {
            case 'e':
                return 0;
            case 'i':
                scanf("%d", &id);
                printf("%d\n", insertItem(arr, m, id));
                break;
            case 's':
                scanf("%d", &id);
                searchItem(arr, m, id);
                break;
            default:
                break;
        }
    }

}

int hash(int m, int id) {
    return id % m;
}

int insertItem(int* arr, int m, int id) {
    int idx = hash(m, id);

    if (arr[idx] == 0) {
        arr[idx] = id;
        return idx;
    }
    else {
        while (1) {
            printf("C");
            idx++;
            if (idx == m) idx = 0;
            if (arr[idx] == 0) {
                arr[idx] = id;
                return idx;
            }
        }
    }
}

void searchItem(int* arr, int m, int id) {
    for (int i = 0; i < m; i++) {
        if (arr[i] == id) {
            printf("%d %d\n", i, id);
            return;
        }
    }
    printf("-1\n");
    return;
}