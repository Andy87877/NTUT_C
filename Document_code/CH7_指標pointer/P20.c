// 指標的指標
#include <stdio.h>

int main() {
    int num = 100;
    int *ptr;
    int **ptr2;
    ptr = &num;
    ptr2 = &ptr;
    printf("num=%d &num=%p\n", num, &num);
    printf("*ptr=%d ptr=%p\n", *ptr, ptr);
    printf("**ptr2=%d *ptr2=%p ptr2=%p\n", **ptr2, *ptr2, ptr2);
}