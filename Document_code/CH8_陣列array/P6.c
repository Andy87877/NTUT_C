// �}�C����}
#include <stdio.h>
#define SIZE 5

int main() {
    int A[SIZE] = {5, 3, 6, 1, 9};
    int i;
    for (i = 0; i < SIZE; i++)
        printf("A[% d] = % 2d, ��}�� % p\n", i, A[i], &A[i]);
    printf("�}�CA����} = % p\n", A);
    return 0;
}