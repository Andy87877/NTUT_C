#include <stdio.h>

int main() {
    double i = 4, j = 6, *p = &j, *q = &i, *r;
    printf("%f %f\n", *p, *q);
    r = p;
    p = q;
    q = r;
    printf("%f %f\n", *p, *q);
}