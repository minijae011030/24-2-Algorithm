//
// Created by 강민재 on 2024. 10. 7..
//

#include <stdio.h>
#include <stdlib.h>

int max_index = -1;

int findElement(int* arr, int k, int n);
int rFindElement(int* arr, int k, int l, int r);

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int* arr = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int result = findElement(arr, k, n);

    if (result == -1) { // 정확한 값이 없을 떄
        printf("%d", max_index);
    } else { // 정확한 값이 있을 때
        printf("%d", result);
    }

    free(arr);
    return 0;
}

int findElement(int* arr, int k, int n) {
    return rFindElement(arr, k, 0, n - 1);
}

int rFindElement(int* arr, int k, int l, int r) {
   if (l > r) return -1;

   int mid = (l + r) / 2;

   if (k == arr[mid]) {
       return mid;
   } else if (k < arr[mid]) {
       return rFindElement(arr, k, l, mid - 1);
   } else {
       if (max_index == -1) {
           max_index = mid;
       } else if (arr[max_index] < arr[mid]) {
           max_index = mid;
       }

       return rFindElement(arr, k, mid + 1, r);
   }

}