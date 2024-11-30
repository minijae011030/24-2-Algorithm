//
// Created by 강민재 on 2024. 10. 7..
//

#include <stdio.h>
#include <stdlib.h>

int min_index = -1;
int findElement(int* arr, int n, int k);

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int result = findElement(arr, n, k);

    if (result == -1) {
        if (min_index == -1)
            printf("%d", n);
        else
            printf("%d", min_index);
    } else {
        printf("%d", result);
    }

    free(arr);

    return 0;
}

int findElement(int* arr, int n, int k) {
    int mid, l = 0, r = n - 1;

    while (1) {
        if (l > r)
            return -1;

        mid = (l + r) / 2;
        if (arr[mid] == k) {
            return mid;
        } else if (arr[mid] > k) {
            if (min_index == -1)
                min_index = mid;
            else if (arr[mid] < arr[min_index])
                min_index = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
}