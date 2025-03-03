// 判斷整數、浮點數、字串
#include <stdio.h>
void f() {
    int ret;
    float n;
    while (1) {
        printf("Integer? ");
        ret=scanf("%f", &n);
        if (ret == 0) {
            printf("char!\n");
        while(getchar()!='\n');
            continue;
        }
        if (ret==1 && n != (int)n) {
            printf("float!\n");
            continue;
        }
        printf("OK\n");
    }
}
int main() {
    f();
    return 0;
}