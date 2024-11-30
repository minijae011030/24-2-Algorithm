#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void downHeap(int arr[], int n, int i); // 힙 정렬을 위한 downHeap 함수
int findKthSmallest(int L[], int n, int k); // k번째 작은 원소를 찾는 함수 (최대 힙 이용)
int* buildList(int n, int min, int max);    // 리스트를 생성하는 함수
void writeList(int L[], int n); // 리스트를 출력하는 함수

// 메인 함수
int main() {
    // 1~100 사이의 무작위 숫자 10개 리스트 생성
    int* L = buildList(10, 1, 100);
    writeList(L, 10);

    // k = 1, 2, 3일 때 k번째 작은 원소 찾기
    for (int k = 1; k <= 3; k++) {
        int kth = findKthSmallest(L, 10, k);
        printf("%d, ", kth);
    }
    printf("\n");

    LARGE_INTEGER ticksPerSec;
    QueryPerformanceFrequency(&ticksPerSec);

    // 1~1000000 사이의 무작위 숫자 100000개 리스트 생성
    int* L_large = buildList(100000, 1, 1000000);
    int k_array[] = { 1, 100, 99900, 99999 };

    // 성능 측정
    for (int i = 0; i < 4; i++) {
        LARGE_INTEGER start, end, diff;

        QueryPerformanceCounter(&start); // 시작 시간 기록
        int kth = findKthSmallest(L_large, 100000, k_array[i]);
        QueryPerformanceCounter(&end);   // 종료 시간 기록

        diff.QuadPart = end.QuadPart - start.QuadPart;
        double cpu_time_used = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);

        printf("%d, %f초\n", kth, cpu_time_used);
    }

    free(L);
    free(L_large);

    return 0;
}

void downHeap(int arr[], int n, int i) {
    int largest = i;    // 현재 노드 인덱스를 가장 큰 노드 인덱스로 설정
    int left = 2 * i + 1;   // 왼쪽 자식 노드 인덱스
    int right = 2 * i + 2;  // 오른쪽 자식 노드 인덱스

    // 왼쪽 자식 노드 인덱스가 힙 배열 내에 있고 largest 인덱스 노드보다 왼족 자식 노드가 더 크면 왼쪽자식 노드 인덱스를 largest로 설정
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 오른쪽 자식 노드 인덱스가 힙 배열 내에 있고 largest 인덱스 노드보다 오른쪽 자식 노드가 더 크면 오른쪽자식 노드 인덱스를 largest로 설정
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // largest가 현재 노드 인덱스와 다르면 교환 후 downheap
    if (largest != i) {
        int tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;

        downHeap(arr, n, largest);
    }
}

int findKthSmallest(int L[], int n, int k) {
    int* heap = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        heap[i] = L[i];
    }

    // 최대 힙을 만들기 위해, k개의 원소가 있는 heap 배열을 재정렬
    // 힙의 절반 지점부터 루트 방향으로 힙 속성을 유지하기 위해 downHeap 호출
    for (int i = k / 2 - 1; i >= 0; i--) {
        downHeap(heap, k, i);
    }

    // 나머지 배열 원소(L[k]부터 L[n-1])와 비교하여, 필요시 힙 갱신
    for (int i = k; i < n; i++) {
        if (L[i] < heap[0]) {
            heap[0] = L[i];
            downHeap(heap, k, 0);
        }
    }

    // 인덱스 0번을 최솟값으로 설정
    int result = heap[0];
    free(heap);
    return result;
}

int* buildList(int n, int min, int max) {
    int* L = (int*)malloc(n * sizeof(int)); // 동적 메모리 할당

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        L[i] = rand() % (max - min + 1) + min;  // 난수 생성
    }

    return L;   // 무순 리스트 반환
}

void writeList(int L[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", L[i]);
    }
    printf("\n");
}