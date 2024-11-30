//
// Created by 강민재 on 2024. 9. 9..
//

#include <stdio.h>
#include <stdlib.h>

void selectionSort(int* arr, int arr_len);   // 선택정렬 함수

int main() {
    int n;
    scanf("%d", &n);

    int *arr = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    selectionSort(arr, n);

    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }

    free(arr);

    return 0;
}

void selectionSort(int* arr, int arr_len) {
    for (int i = arr_len - 1; i > 0; i--) {
        int max_idx = i;
        for (int j = 0; j <  i; j++) {
            if (arr[j] > arr[max_idx]) {
                max_idx = j;
            }
        }

        if (max_idx != i) {
            int tmp = arr[i];
            arr[i] = arr[max_idx];
            arr[max_idx] = tmp;
        }
    }
}

