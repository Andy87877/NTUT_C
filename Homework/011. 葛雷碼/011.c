#include <math.h>
#include <stdio.h>

void G(int n, int k) {
    if (n == 1) {
        printf("%d", k);
        return;
    }
    if (k < (pow(2, n - 1))) {
        printf("0");
        return G(n - 1, k);
    } else {
        printf("1");
        return G(n - 1, pow(2, n) - 1 - k);
    }
}

void Judge(int n, int k) {
    G(n, k);
    printf("\n");
}

int main() {
    int n, k;
    while (1 == 1) {
        scanf("%d", &n);
        if (n == -1) {
            break;
        }
        scanf("%d", &k);
        Judge(n, k);
    }
}