#include <stdio.h>

void function(int* a, int* b, int* c) {
    int* temp = a;
    *b = (*c) * (*temp);
    *c = *temp;
    *a = 10;
    a = b;
    b = c;
    c = temp;
}
void main(void) {
    int i = -1, j = 4, k = 2, *p = &i, *q = &j;
    function(p, q, &k);
    printf("%d %d %d\n", i, j, k);
}