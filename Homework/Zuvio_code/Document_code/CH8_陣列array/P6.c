// 陣列的位址
#include <stdio.h>
#define SIZE 5

int main() {
    int A[SIZE] = {5, 3, 6, 1, 9};
    int i;
    for (i = 0; i < SIZE; i++)
        printf("A[% d] = % 2d, 位址為 % p\n", i, A[i], &A[i]);
    printf("陣列A的位址 = % p\n", A);
    return 0;
}