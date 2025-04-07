#include <stdio.h>

void f21(int *s, int p[][3]) {
    *s = p[1][2];
    *(++s) = p[1][1];
}
int f22(int a[], int n) {
    if (n > 1) {
        printf("%d\n", a[n]);
        return f22(a, n - 1) + a[n];
    } else
        return 0;
}
int f23(int m, int n) {
    if (m % n == 0)
        return n;
    else
        printf("%d, %d\n", m, n);
    return f23(n, m % n);
}
void f2() {
    int result;
    int b[] = {2, 3, 4, 1, 0, 5};
    int a[2][3] = {5, 3, 2, 1, 4, 7}, *p;
    p = &b[2];
    f21(p, a);
    printf("%d, %d\n", b[2], b[3]);
    p = &b[1];
    result = f22(p, b[1]);
    f23(75, p[2] + 32);
}

int main() { f2(); }