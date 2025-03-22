// 不定參數
#include <stdio.h>
#include <stdarg.h>
void foo(int len, ...) {
    va_list args;
    va_start(args, len);
    for(int j = 0; j < len; j++) {
        printf("%.1f\n", va_arg(args, double));
    }
    va_end(args);
}
int main() {
    double x = 1.1, y = 2.1, z = 3.9;
    double a = 0.1, b = 0.2, c = 0.3;
    foo(3, x, y, z);
    printf("=\n");
    foo(6, x, y, z, a, b, c);
    return 0;
}