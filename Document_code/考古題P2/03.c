#include <stdio.h>

#define size 7
void Print_array(int a[]){
    for (int i = 0; i < 5; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

void f31(int **pp, int **qq, int a[], int *p) {
    Print_array(a);
    int **rr = qq;
    a[1] = (**rr) + (*(a + 2));
    printf("%d\n", a[1]); // (1)
    Print_array(a);
    *pp = p + 1;
    *rr = *pp + 1;
    printf("%d\n", *(*rr + 3)); // (2)
    *(a + 1) += (**pp) + *((*pp - 5) + *(p + 1));
    printf("*(a + 1): %d %d\n", **pp, *((*pp - 5) + *(p + 1)));
    Print_array(a);
    printf("%d\n", a[1]); // (3)
    *qq = p + 1;
    *((*qq) + 1) = (**rr) + (**pp);
    printf("%d\n", **qq); // (4)
}
void f3() {
    int a[] = {3, 4, 5, 6, 7, 8, 9};
    int *p = a, *q = a + 2;
    int **pp = &p;
    f31(pp, &q, a + 2, p);
}

int main() { f3(); }