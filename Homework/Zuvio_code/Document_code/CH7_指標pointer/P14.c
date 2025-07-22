#include <stdio.h>
#include <stdlib.h>
int main() {
    float *f = (float *)malloc(sizeof(float));
    *f = 100.09;
    printf("f=%p  &f=%p  *f=%.2f\n", f, &f, *f);
    free(f);
    printf("f=%p  &f=%p  *f=%.2f\n", f, &f, *f);
}