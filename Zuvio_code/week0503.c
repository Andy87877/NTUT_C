#include <stdio.h>

void f(int **a, int **b, int **c, int *d){
    *a = d;
    **b = (**a)/(**c);
    *d = (**b)*(**a);
}

int testF(){
    int i = 5, j = -2, k = 9, *p = &i, *q = &j, *x = &k;
    f(&p, &q, &x, &k);
    printf("%d %d %d\n", i, j, k);
}

void g(int **a, int **b, int **c, int *d){
    int **temp = a;
    a = b;
    b = temp;
    *a = d;
    (**a) = (**b) + (**c);
}

int testG(){
    int i = 5, j = -2, k = 9, *p = &i, *q = &j, *x = &k;
    g(&p, &q, &x, &k);
    printf("%d %d %d\n", i, j, k);
}

int main(){
    // testF();
    testG();
    return 0;
}