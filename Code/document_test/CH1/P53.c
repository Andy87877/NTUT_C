#include <stdio.h>
#include <time.h>
long g(int n) {
    if (n<1) return 1;
    else return (g(n-1)+g(n-2)+g(n-3));
}
int main() {
    long begin, end;
    begin = clock();
    g(32);
    end = clock();
    printf("%d ms\n", (end-begin)*100/CLK_TCK); //毫秒
    return 0;
}