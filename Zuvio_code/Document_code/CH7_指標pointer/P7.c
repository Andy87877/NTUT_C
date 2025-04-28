#include <stdio.h>

int main() {
    int x = 1001, *p;
    *p = x;
    printf("%d", *p);
}