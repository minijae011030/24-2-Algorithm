//
// Created by 강민재 on 2024. 10. 7..
//

#include <stdio.h>
#include <stdlib.h>

int findElement(char* cmd, int l, int r);

int main() {
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    getchar();

    char* cmd = (char*)malloc(sizeof(char) * (n + 1));
    gets(cmd);

    printf("%d", findElement(cmd, a, b));
    return 0;
}

int findElement(char* cmd, int l, int r) {
    int idx = 0;

    while (1) {
        int mid = (l + r) / 2;

        if (l == r) return l;

        if (cmd[idx] == 'Y') l = mid + 1;
        else r = mid;

        idx++;
    }
}