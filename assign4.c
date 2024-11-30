//
// Created by 강민재 on 2024. 11. 21..
//

#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 60

int A[MAX], H[MAX];

int airtelDC(int s, int d); // 분할정복(DC) 방식
int airtelDP(int s, int d); // 동적 프로그래밍(DP) 방식

int main() {
    // 배열 A와 H 초기화
    // A[i]는 항공 요금, H[i]는 숙박 요금
    A[0] = 0, H[0] = 0;
    for (int i = 1; i < MAX; i++) {
        A[i] = A[i - 1] + (A[i - 1] + 1) % 5 + 3; // 항공 요금 초기화
        H[i] = (H[i - 1] + i) % 9 + 1;           // 숙박 요금 초기화
    }

    // 테스트 실행
    int n = 6; // 초기 테스트 도시 개수
    int test_cases[3][2] = {{0, 4}, {2, 5}, {2, 4}}; // 테스트 케이스 (s: 시작 도시, d: 도착 도시)
    printf("n\ts\td\tmincost\tversion\t\tcputime\n");

    // 작은 n 테스트
    for (int t = 0; t < 3; t++) {
        int s = test_cases[t][0], d = test_cases[t][1];

        // 분할정복 방식 실행 및 시간 측정
        clock_t start = clock();
        int costDC = airtelDC(s, d);
        clock_t end = clock();
        printf("%d\t%d\t%d\t%d\t\tDC\t\t\t%.6f\n",
               n, s, d, costDC, (double)(end - start) / CLOCKS_PER_SEC * 1000);

        // 동적 프로그래밍 방식 실행 및 시간 측정
        start = clock();
        int costDP = airtelDP(s, d);
        end = clock();
        printf("%d\t%d\t%d\t%d\t\tDP\t\t\t%.6f\n",
               n, s, d, costDP, (double)(end - start) / CLOCKS_PER_SEC * 1000);
    }

    // 큰 n 테스트
    n = MAX; // 최대 도시 수 설정
    int s = 1, d = 28; // 시작 도시 s = 1, 도착 도시 d = 28

    // 분할정복 방식 실행 및 시간 측정
    clock_t start = clock();
    int costDC = airtelDC(s, d);
    clock_t end = clock();
    printf("%d\t%d\t%d\t%d\t\tDC\t\t\t%.6f\n",
           n, s, d, costDC, (double)(end - start) / CLOCKS_PER_SEC * 1000);

    // 동적 프로그래밍 방식 실행 및 시간 측정
    start = clock();
    int costDP = airtelDP(s, d);
    end = clock();
    printf("%d\t%d\t%d\t%d\t\tDP\t\t\t%.6f\n",
           n, s, d, costDP, (double)(end - start) / CLOCKS_PER_SEC * 1000);

    return 0;
}

/**
 * 분할정복(DC) 방식
 * @param s : 시작 도시
 * @param d : 도착 도시
 * @return minCost: s에서 d까지의 최소 비용
 */
int airtelDC(int s, int d) {
    if (s == d) return 0; // 기본 케이스: 시작 도시와 도착 도시가 같으면 비용은 0

    int minCost = INT_MAX; // 최소 비용 초기화
    for (int k = s + 1; k <= d; k++) {
        // k를 중간 경유지로 설정하고 비용 계산
        int cost = airtelDC(s, k - 1) + H[k - 1] + A[d - k];
        if (cost < minCost) {
            minCost = cost; // 최소 비용 갱신
        }
    }

    return minCost; // 최소 비용 반환
}


/**
 * 동적 프로그래밍(DP) 방식
 * @param s : 시작 도시
 * @param d : 도착 도시
 * @return minCost: s에서 d까지의 최소 비용
 */
int airtelDP(int s, int d) {
    int dp[MAX][MAX]; // DP 테이블 초기화
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            dp[i][j] = INT_MAX; // 초기 값을 무한대(INT_MAX)로 설정
        }
    }

    for (int i = s; i <= d; i++) {
        dp[i][i] = 0; // 자기 자신으로 가는 비용은 0
    }

    for (int len = 1; len <= d - s; len++) { // 도시 간 거리(len)를 증가시키며 계산
        for (int i = s; i + len <= d; i++) { // 시작 도시
            int j = i + len; // 도착 도시
            for (int k = i + 1; k <= j; k++) { // 경유 도시
                int cost = dp[i][k - 1] + H[k - 1] + A[j - k]; // 비용 계산
                if (cost < dp[i][j]) {
                    dp[i][j] = cost; // 최소 비용 갱신
                }
            }
        }
    }

    return dp[s][d]; // s에서 d까지의 최소 비용 반환
}
