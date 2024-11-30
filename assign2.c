#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n = 100000;
int Limits[4] = {1, 100, 500, 1000};

// 함수 선언
int* createArray();
void quickSort(int* A, int n, int Limit, int mode);
void rQuickSort(int* A, int left, int right, int Limit, int mode);
int findPivot(int* A, int left, int right, int mode);
void insertionSort(int* A, int left, int right);
void inPlacePartition(int* A, int left, int right, int k, int* a, int* b);
void swap(int* a, int* b);
void printElapsedTime(clock_t start, clock_t end);

int main() {
    int* A = createArray();
    printf("Limit    결정적1         결정적3        무작위1         무작위3\n");
    for (int i = 0; i < 4; i++) {
        printf("%-8d", Limits[i]);  // Limit 값을 8칸 폭으로 출력하여 정렬
        for (int j = 0; j < 4; j++) {
            int* A_copy = (int*)malloc(sizeof(int) * n);

            for (int k = 0; k < n; k++) {
                A_copy[k] = A[k];  // 배열 복사
            }

            clock_t start = clock();  // 시작 시간 측정
            quickSort(A_copy, n, Limits[i], j + 1);
            clock_t end = clock();    // 종료 시간 측정

            printElapsedTime(start, end);  // 소요 시간 출력

        }
        printf("\n");
    }

    return 0;
}

// 배열 생성 함수
int* createArray() {
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n + 1; // 1부터 n까지의 랜덤한 정수
    }
    return arr;
}

// 퀵 정렬 함수
void quickSort(int* A, int n, int Limit, int mode) {
    rQuickSort(A, 0, n - 1, Limit, mode);
}

// 재귀 퀵 정렬 함수
void rQuickSort(int* A, int left, int right, int Limit, int mode) {
    if (right - left <= Limit) {
        insertionSort(A, left, right);  // 작은 부분 배열에 대해 삽입정렬 수행
        return;
    }

    int k = findPivot(A, left, right, mode);  // 피벗 선택
    int a, b;
    inPlacePartition(A, left, right, A[k], &a, &b);  // 피벗 값으로 배열 분할

    rQuickSort(A, left, a - 1, Limit, mode);  // 왼쪽 부분 배열 재귀 호출
    rQuickSort(A, b + 1, right, Limit, mode); // 오른쪽 부분 배열 재귀 호출
}

// 피벗 선택 함수
int findPivot(int* A, int left, int right, int mode) {
    if (mode == 1) return right;    // deterministic1
    if (mode == 2) return left + rand() % (right - left + 1);   // randomized1
    if (right - left == 1) return left;

    int a, b, c;
    if (mode == 3) { a = left, b = (left + right) / 2, c = right; }  // deterministic3
    if (mode == 4) {  // randomized3
        a = left + rand() % (right - left + 1);
        b = left + rand() % (right - left + 1);
        c = left + rand() % (right - left + 1);
    }

    // 중앙값 선택
    int mid = (A[a] < A[b]) ? ((A[b] < A[c]) ? b : (A[a] < A[c] ? c : a)) : ((A[a] < A[c]) ? a : (A[b] < A[c] ? c : b));
    return mid;
}

// 삽입 정렬 함수
void insertionSort(int* A, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= left && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

// 분할 함수 (피벗 값을 기준으로 배열을 두 부분으로 나누는 작업)
void inPlacePartition(int* A, int left, int right, int pivotValue, int* a, int* b) {
    int i = left;  // 현재 탐색 중인 인덱스
    int lt = left; // 피벗보다 작은 값들이 위치하는 경계
    int gt = right; // 피벗보다 큰 값들이 위치하는 경계

    while (i <= gt) {
        if (A[i] < pivotValue) {   // 피벗보다 작은 값과 교환
            swap(&A[i], &A[lt]);
            i++;
            lt++;
        } else if (A[i] > pivotValue) {    // 피벗보다 큰 값과 교환
            swap(&A[i], &A[gt]);
            gt--;
        } else {    // 피벗과 같은 값은 그냥 넘김
            i++;
        }
    }

    *a = lt;
    *b = gt;
}

// 교환 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printElapsedTime(clock_t start, clock_t end) {
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;  // 밀리초 단위
    printf(" %.8f   ", time_spent);
}