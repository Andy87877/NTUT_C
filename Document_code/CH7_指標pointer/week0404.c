#include <stdio.h>

int main() {
    int i, j = 21, *p = &j, *q = p;
    printf("%d %d\n", *p, *q);
    for (i = 0; i < 4; i++) *(p++); // ==>p++
    (*q)++;
    printf("%d %d %d", *p, *q, i);
}