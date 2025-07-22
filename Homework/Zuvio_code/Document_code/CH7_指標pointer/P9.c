#include <stdio.h>
void f() {
    const char* str1 = "test";
    const char* str2 = "test";
    printf("%d\n%d\n", str1, str2);
}
int main() {
    const char* str = "test";
    f();
    printf("%d", str);
    return 0;
}