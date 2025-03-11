#include <stdio.h>

int main() {
    int i = 4, *p = &i, *q = &i;
    printf("%d %d\n", *p, *&i);
    i += (*q) * (*p);
    printf("%d %d\n", i, q);
}