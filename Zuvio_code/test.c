#include <stdio.h>
#include <string.h> // 宣告 int strcmp( const char *lhs, const char *rhs );
void check(char *a, char *b, int (*cmp)(const char *, const char *)) {
    if (!(*cmp)(a, b))
        printf("equal");
    else
        printf("not equal");
}
void test() {
    char s1[80], s2[80];
    int (*p)(const char *, const char *);
    p = strcmp;
    fgets(s1, 80, stdin);
    fgets(s2, 80, stdin);
    check(s1, s2, p);
}
int main() {
    test();
    return 0;
}