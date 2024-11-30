//
// Created by 강민재 on 2024. 9. 23..
//

#include <stdio.h>

int H[100];
int n;

void inPlaceHeapSort();
void printArray();

void downHeap(int i, int last);
void rBuildHeap(int i);

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &H[i]);
    }

    rBuildHeap(1);

    inPlaceHeapSort();
    printArray();

    return 0;
}

void inPlaceHeapSort() {
    int tmp, s;
    s = n;
    for (int i = s; i >= 2; i--) {
        tmp = H[1];
        H[1] = H[i];
        H[i] = tmp;
        s--;

        downHeap(1, s);
    }
}

void printArray() {
    for (int i = 1; i <= n; i++) {
        printf(" %d", H[i]);
    }
    printf("\n");
    return;
}

void downHeap(int i, int last) {
    int left = i * 2;//왼쪽 자식
    int right = i * 2 + 1;//오른쪽 자식
    int big, tmp;
    if (last < left && last < right)
        return;

    big = left;
    if (last >= right) {
        if (H[big] < H[right]) {
            big = right;
        }
    }

    if (H[big] <= H[i])
        return;

    tmp = H[i];
    H[i] = H[big];
    H[big] = tmp;

    downHeap(big, last);
}

void rBuildHeap(int i) { // 상향식 힙 생성 함수
    if (i > n) {
        return;
    }
    rBuildHeap(i * 2);
    rBuildHeap(i * 2 + 1);
    downHeap(i, n);

    return;
}

