#include <stdio.h>

int main() {
    char c = '1';
    int i = 1;
    float f = 1.0f;
    double d = 1.0f;
    char *cPtr = &c;
    int *nPtr = &i;
    float *fPtr = &f;
    double *dPtr = &d;
    printf("cPtr sizes: %d\n", sizeof(cPtr));
    printf("nPtr sizes: %d\n", sizeof(nPtr));
    printf("fPtr sizes: %d\n", sizeof(fPtr));
    printf("dPtr sizes: %d\n", sizeof(dPtr));
}