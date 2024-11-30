//
// Created by 강민재 on 2024. 9. 15..
//

#include <stdio.h>

int H[100]; // 힙
int n = 0;  // 힙의 크기

void downHeap(int i);
void printHeap();

void rBuildHeap(int i);
void buildHeap();

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &H[i]);
    }

    buildHeap();

    printHeap();

    return 0;
}


/**
 * 인자: 배열 인덱스 i
 * 반환값: 없음
 * 내용: 힙 내 위체 i에 저장된 키를 크기에 맞는 위치로 하향 이동
 * 시간 성능: O(log n)
 *
 * @param i 배열 인덱스
 */
void downHeap(int i) {
    int left_child = 2 * i; // 왼쪽 자식 노드 인덱스
    int right_child = 2 * i + 1;    // 오른쪽 자식 노드 인덱스

    if (left_child > n && right_child > n) return;  // 자식 노드가 없으면 리턴

    // 큰 자식 노드 찾기
    int large_child;

    if (right_child <= n && H[right_child] > H[left_child])
        large_child = right_child;
    else
        large_child = left_child;

    // 현재 노드가 큰 자식 노드보다 크면 종료
    if (H[i] >= H[large_child]) return;

    // 현재 노드가 큰 자식 노드보다 작으면 교환
    int tmp = H[i];
    H[i] = H[large_child];
    H[large_child] = tmp;

    // 큰 자식 노드로 downHeap 수행
    return downHeap(large_child);
}

/**
 * 인자: 없음
 * 반환값: 없음
 * 내용: 힙에 저장된 키들을 레벨순서로 인쇄
 * 시간 성능: O(n)
 */
void printHeap() {
    for (int i = 1; i <= n; i++) printf(" %d", H[i]);

    printf("\n");

    return;
}

/**
 * 인자: 정수 i (부분 힙의 루트 인덱스)
 * 반환값: 없음
 * 내용: 재귀 방식으로 상향식 힙 생성
 *
 * @param i 부분 힙의 루트 인덱스
 */
void rBuildHeap(int i) {
    if (i > n) return;

    rBuildHeap(2 * i);  // 현재 부트리의 좌 부트리를 힙 생성
    rBuildHeap(2 * i + 1);  // 현재 부트리의 우 부트리를 힙 생성
    downHeap(i);    // 현재 부트리의 루트와 좌우 부트리를 합친 힙 생성

    return;
}

/**
 * 인자: 없음
 * 반환값: 없음
 * 내용: 비재귀 방식으로 상향식 힙 생성
 * 시간 성능: O(n)
 */
void buildHeap() {
    for (int i = n / 2; i >= 1; i--) {
        downHeap(i);
    }

    return;
}