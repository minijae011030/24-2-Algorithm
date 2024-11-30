//
// Created by 강민재 on 2024. 9. 15..
//

#include <stdio.h>
#include <stdlib.h>

void insertionSort(int* arr, int arr_len); // 삽입정렬 함수

int main() {
    int n;
    scanf("%d", &n);

    int *arr = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    insertionSort(arr, n);

    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }

    free(arr);

    return 0;
}

void insertionSort(int* arr, int arr_len) {
    for (int i = 1; i < arr_len; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 힙 구조를 유지하는 함수 (힙 정렬의 핵심 부분)
void heapify(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 왼쪽 자식이 루트보다 크다면 가장 큰 값을 왼쪽 자식으로 설정
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // 오른쪽 자식이 가장 큰 값보다 크다면 가장 큰 값을 오른쪽 자식으로 설정
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 가장 큰 값이 루트가 아니라면 교환하고 힙 속성을 재정렬
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // 재귀적으로 힙 구조를 유지
        heapify(arr, n, largest);
    }
}

// 힙 정렬 메인 함수
void heapSort(int* arr, int n) {
    // 배열을 힙 구조로 변환 (최대 힙 생성)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 하나씩 요소를 힙에서 꺼내어 정렬
    for (int i = n - 1; i > 0; i--) {
        // 루트(가장 큰 값)와 마지막 요소를 교환
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // 힙의 크기를 줄이고 힙 속성을 재정렬
        heapify(arr, i, 0);
    }
}
