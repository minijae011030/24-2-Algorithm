//
// Created by 강민재 on 2024. 9. 30..
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b);


int findPivot(int l, int r); // findPivot 함수: 피벗을 단순히 r 위치로 설정
void inPlacePartition(int arr[], int l, int r, int pivot, int* a, int* b);  // inPlacePartition 함수: 피벗을 기준으로 배열을 나누는 함수
void inPlaceQuickSort(int arr[], int l, int r); // inPlaceQuickSort 함수: 퀵 정렬을 재귀적으로 수행하는 함수

int main() {
    int n;
    scanf("%d", &n);    // 배열 크기 입력

    int arr[n];
    for (int i = 0; i < n; i++) {   // 배열 요소 입력
        scanf("%d", &arr[i]);
    }

    srand(time(NULL));  // 난수 생성 초기화
    inPlaceQuickSort(arr, 0, n - 1);    // 퀵 정렬 함수 실행

    for (int i = 0; i < n; i++) {   // 결과 출력
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int findPivot(int l, int r) {
    int pivotIndex = l + rand() % (r - l + 1); // l과 r 사이의 무작위 인덱스 반환
    return pivotIndex;
}

void inPlacePartition(int arr[], int l, int r, int pivot, int* a, int* b) {
    int i = l;  // 현재 탐색 중인 인덱스
    int lt = l; // pivot 보다 작은 값들이 위치하는 경계
    int gt = r; // pivot 보다 큰 값들이 위치하는 경계

    // l ~ r 탐색
    while (i <= gt) {
        if (arr[i] < pivot) {   // 현재 인덱스 원소가 pivot 보다 작으면 lt와 교환 후 lt, i 증가
            swap(&arr[i], &arr[lt]);
            i++;
            lt++;
        } else if (arr[i] > pivot) {    // 현재 인덱스 원소가 pivot 보다 크면 교환 후 gt 감소
            swap(&arr[i], &arr[gt]);
            gt--;
        } else {    // 현재 인덱스 원소가 pivot과 같으면 i 증가
            i++;
        }
    }

    // 경계 조정
    *a = lt;
    *b = gt;
}

void inPlaceQuickSort(int arr[], int l, int r) {
    // l이 r보다 크거나 같으면 정렬할 필요 없음
    if (l >= r) {
        return;
    }

    int k = findPivot(l, r);   // 무작위 pivot 위치 선택
    int a, b;

    inPlacePartition(arr, l, r, arr[k], &a, &b);    // 배열을 pivot을 기준으로 나눔
    inPlaceQuickSort(arr, l, a - 1);    // pivot 보다 작은 부분을 정렬
    inPlaceQuickSort(arr, b + 1, r);    // pivot 보다 큰 부분을 정렬
}
