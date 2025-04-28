#include <stdio.h>
void f(int a, int* b, int* c) {
    int d;
    a = 2;
    *b = 3;
    c = &a;
    d = 5;
    printf("%d %d %d %d\n", a, b, c, d);
}
int main() {
    int a = 1, b = 2, c = 3, d = 4;
    f(a, &b, &c);
    printf("%d %d %d %d\n", a, b, c, d);
    return 0;
}