#include <stdio.h>

int main() {
    int i = 4, j, number = 3, *p = &number;
    for (j = 0; j < number; j++) {
        (*p) += i--;
    }
    printf("%d %d %d %d\n", *p, number, j, i);
}