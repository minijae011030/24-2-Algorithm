//
// Created by 강민재 on 2024. 9. 15..
//

#include <stdio.h>

int H[100]; // 힙
int n = 0;  // 힙의 크기

void insertItem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();

int main() {
    int key;
    char cmd;
    while (1) {
        scanf("%c", &cmd);

        switch (cmd) {
            case 'i':
                scanf("%d", &key);
                insertItem(key);
                printf("0\n");
                break;
            case 'd':
                key = removeMax();
                printf("%d\n", key);
                break;
            case 'p':
                printHeap();
                break;
            case 'q':
                return 0;
        }
    }
}

/**
 * 인자: 정수 key
 * 반환값: 없음
 * 내용: n 위치에 key 삽입, upHeap(n) 호출 수행 후 n(총 키 개수)을 갱신
 * 시간 성능: O(log n)
 *
 * @param key n 위치에 삽입할 정수
 */
void insertItem(int key) {
    n++;    // n 갱신
    H[n] = key; // 힙의 초기 삽입 위치는 n

    upHeap(n);  // 힙 조정

    return;
}

/**
 * 인자: 없음
 * 반환값: 삭제된 키(정수)
 * 내용: downHeap 호출 수행 후 n(총 키 개수)을 갱신
 * 시간 성능: O(log n)
 *
 * @return 삭제된 가장 큰 값 반환
 */
int removeMax() {
    int key = H[1]; // 루트 키 보관

    H[1] = H[n];    // 힙의 마지막 키를 루트로 이동
    n--;    // n 갱신

    downHeap(1);    // 힙 조정

    return key; // 삭제 키 반환
}

/**
 * 인자: 배열 인덱스 i
 * 반환값: 없음
 * 내용: 힙 내 위체 i에 저장된 키를 크기에 맞는 위치로 상향 이동
 * 시간 성능: O(log n)
 *
 * @param i 상향 이동을 검사할 배열 인덱스
 */
void upHeap(int i) {
    if (i == 1) return; // 루트 노드이면 종료

    if (H[i] <= H[i / 2]) return;  // 현재 노드의 키가 부모 노드의 키보다 작거나 같으면 종료

    // 현재 노드의 키가 부모 노드의 키보다 크면 교환
    int tmp = H[i];
    H[i] = H[i / 2];
    H[i / 2] = tmp;

    // 부모 노드로 upHeap 수행
    return upHeap(i / 2);

}

/**
 * 인자: 배열 인덱스 i
 * 반환값: 없음
 * 내용: 힙 내 위체 i에 저장된 키를 크기에 맞는 위치로 하향 이동
 * 시간 성능: O(log n)
 *
 * @param i 하향 이동을 검사할 배열 인덱스
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